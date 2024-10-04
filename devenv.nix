{pkgs, ...}: {
  # https://devenv.sh/basics/
  env.GREET = "devenv";

  # https://devenv.sh/packages/
  packages = with pkgs; [git];

  # https://devenv.sh/languages/
  languages.cplusplus.enable = true;

  # https://devenv.sh/processes/
  # processes.cargo-watch.exec = "cargo-watch";

  # https://devenv.sh/services/
  # services.postgres.enable = true;

  # https://devenv.sh/scripts/
  scripts.hello.exec = ''
    echo hello from $GREET
  '';

  enterShell = ''
    hello
    git --version
  '';

  # https://devenv.sh/tasks/
  # tasks = {
  #   "myproj:setup".exec = "mytool build";
  #   "devenv:enterShell".after = [ "myproj:setup" ];
  # };

  # https://devenv.sh/tests/
  enterTest = ''
    echo "Running tests"
    git --version | grep --color=auto "${pkgs.git.version}"
  '';

  # https://devenv.sh/pre-commit-hooks/
  pre-commit.hooks = {
    # C++
    clang-format = {
      enable = true;
      types_or = ["c++" "c"];
    };
    clang-tidy = {
      enable = false;
      types_or = ["c++" "c"];
      entry = "clang-tidy -p build --fix";
    };
    clazy = {
      enable = false;
      types = ["c++"];
      entry = "clazy-standalone -p build/compile_commands.json";
    };
    cppcheck = {
      enable = false;
      types = ["c++"];
      entry = ''
        cppcheck \
            --check-level=exhaustive \
            --enable=performance \
            --enable=portability \
            --enable=style \
            --enable=warning \
            --library=qt \
            --error-exitcode=1 \
            --inline-suppr \
            --suppress=unusedStructMember
      '';
    };
    flawfinder = {
      enable = false;
      pass_filenames = false;
      entry = "flawfinder --error-level=0 ./src";
    };

    # CMake
    cmake-format = {
      enable = true;
      types = ["cmake"];
      entry = "cmake-format -c .cmake.yaml -i";
    };
    cmake-lint = {
      enable = true;
      types = ["cmake"];
      entry = "cmake-lint -c .cmake.yaml";
    };

    # nix
    alejandra.enable = true;
    deadnix.enable = true;
    flake-checker.enable = true;
    nil.enable = true;
    statix.enable = true;
  };

  # See full reference at https://devenv.sh/reference/options/
}
