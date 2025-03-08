# f-koehler' LeetCode Solutions

[![CI](https://github.com/f-koehler/LeetCode/actions/workflows/ci.yml/badge.svg)](https://github.com/f-koehler/LeetCode/actions/workflows/ci.yml)

This repository contains my LeetCode solutions. They are mostly in C++ but recently I started to solve the problems with Python and Rust as well. The [`fetch_problem.py`](#start-working-on-problem) script makes it easy to start working on a new problem by fetching its description and preparing the boilerplate for C++, Python, and Rust.

## Description

This project is designed to help developers efficiently fetch and start working on new problems. It provides a script to simplify the process of setting up the environment and fetching problem statements or templates.

## Start Working on Problem

The `fetch_problem.sh` script is a utility to quickly set up the working environment for a new problem. It automates the retrieval of problem description and adds C++, Rust, and Python sources including the example test cases. To fetch a problem just call the script with the problem number:

```bash
./fetch_problem.py 136
```

## Nix

If you have `nix` available, you can very easily setup a development environment with the required packages and some nice git hooks using

```bash
nix develop --no-pure-eval
```
