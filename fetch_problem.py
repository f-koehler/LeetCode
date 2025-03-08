#!/usr/bin/env -S uv run
import typer
from typing import Annotated
import requests
import datetime
from cachier import cachier
from typing import Any
from dataclasses import dataclass
import html
import jinja2
from pathlib import Path
from bs4 import BeautifulSoup


@dataclass
class ProblemEntry:
    id: int
    frontend_id: int
    title: str
    slug: str
    difficullty: int

    @staticmethod
    def from_json(json: dict[str, Any]) -> "ProblemEntry":
        return ProblemEntry(
            id=json["stat"]["question_id"],
            frontend_id=json["stat"]["frontend_question_id"],
            title=json["stat"]["question__title"],
            slug=json["stat"]["question__title_slug"],
            difficullty=json["difficulty"]["level"],
        )


def extract_examples(html_content: str) -> list[tuple[str, str]]:
    soup = BeautifulSoup(html_content, "html.parser")

    examples = []

    # Find all the <pre> tags, which contain the Input and Output
    pre_tags = soup.find_all("pre")

    # Loop through the pre_tags and extract the corresponding input and output
    for pre_tag in pre_tags:
        # Extract text from the <pre> tag
        text = pre_tag.get_text(strip=True)

        # Find the position of 'Input:' and 'Output:'
        if "Input:" in text and "Output:" in text:
            input_text = text.split("Input:")[1].split("Output:")[0].strip()
            output_text = (
                text.split("Output:")[1].split("Explanation:")[0].strip()
            )  # Exclude explanation if any
            examples.append((input_text, output_text))

    return examples


@dataclass
class Problem:
    id: int
    slug: str
    title: str
    description: str
    difficulty: str
    tags: list[str]
    test_cases: list[tuple[str, str]]
    code_snippets: dict[str, str]

    @staticmethod
    def from_json(slug: str, data: dict[str, Any]) -> "Problem":
        test_cases = data["exampleTestcases"].split("\n")
        return Problem(
            id=int(data["questionId"]),
            slug=slug,
            title=data["title"],
            description=data["content"],
            difficulty=data["difficulty"],
            tags=data["topicTags"],
            test_cases=extract_examples(data["content"]),
            code_snippets={
                snippet["langSlug"]: snippet["code"] for snippet in data["codeSnippets"]
            },
        )


@cachier(stale_after=datetime.timedelta(days=3))
def fetch_all_problems():
    url = "https://leetcode.com/api/problems/all"
    response = requests.get(url, allow_redirects=True)
    response.raise_for_status()
    return response.json()


@cachier(stale_after=datetime.timedelta(days=3))
def fetch_problem(title_slug):
    url = "https://leetcode.com/graphql"
    query = """
    query getQuestionDetail($titleSlug: String!) {
      question(titleSlug: $titleSlug) {
        questionId
        title
        content
        difficulty
        topicTags {
          name
        }
        exampleTestcases
        codeSnippets {
          lang
          langSlug
          code
        }
      }
    }
    """
    variables = {"titleSlug": title_slug}

    response = requests.post(url, json={"query": query, "variables": variables})
    if response.status_code == 200:
        data = response.json()
        problem = data["data"]["question"]

        # Extract and clean up data
        problem["content"] = html.unescape(problem["content"])  # Decode HTML entities
        problem["topicTags"] = [tag["name"] for tag in problem["topicTags"]]

        return problem
    else:
        raise Exception(f"Failed to fetch problem: {response.status_code}")


def zfill_filter(text: str, length: int) -> str:
    return text.zfill(length)


def main(id: Annotated[int, typer.Argument()]):
    # remove paid problems
    problem_entries: list[ProblemEntry] = [
        ProblemEntry.from_json(problem)
        for problem in fetch_all_problems()["stat_status_pairs"]
        if not problem["paid_only"]
    ]
    entry = next(filter(lambda p: p.id == id, problem_entries))
    problem = Problem.from_json(entry.slug, fetch_problem(entry.slug))

    env = jinja2.Environment(loader=jinja2.FileSystemLoader("templates"))
    env.filters["zfill"] = zfill_filter

    # store problem HTML locally
    file_stem = f"p{str(problem.id).zfill(4)}_{problem.slug}".replace("-", "_")
    env.get_template("problem.html.j2").stream(problem=problem).dump(
        str(Path("src") / f"{file_stem}.html")
    )

    # generate template for rust solution
    rust_path = Path("src") / f"{file_stem}.rs"
    if not rust_path.exists():
        rust_path.write_text(env.get_template("problem.rs.j2").render(problem=problem))

    env.get_template("lib.rs.j2").stream(
        rust_modules=[
            file.stem
            for file in Path("src").iterdir()
            if file.is_file() and file.suffix == ".rs" and file.stem.startswith("p")
        ]
    ).dump("src/lib.rs")

    # generate template for the C++ solution
    cpp_path = Path("src") / f"{file_stem}.cpp"
    if not cpp_path.exists():
        cpp_path.write_text(env.get_template("problem.cpp.j2").render(problem=problem))

    env.get_template("sources.cmake.j2").stream(
        cpp_sources=[
            file.stem
            for file in Path("src").iterdir()
            if file.is_file() and file.suffix == ".cpp" and file.stem.startswith("p")
        ]
    ).dump("sources.cmake")

    # generate template for the Python solution
    py_path = Path("src") / f"{file_stem}.py"
    if not py_path.exists():
        py_path.write_text(env.get_template("problem.py.j2").render(problem=problem))


if __name__ == "__main__":
    typer.run(main)
