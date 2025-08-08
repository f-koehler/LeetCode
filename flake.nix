{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    systems.url = "github:nix-systems/default";
    devenv.url = "github:cachix/devenv";
    devenv.inputs.nixpkgs.follows = "nixpkgs";
  };

  nixConfig = {
    extra-trusted-public-keys = "devenv.cachix.org-1:w1cLUi8dv3hnoSPGAuibQv+f9TZLr6cv/Hm9XgU50cw=";
    extra-substituters = "https://devenv.cachix.org";
  };

  outputs =
    {
      self,
      nixpkgs,
      devenv,
      systems,
      ...
    }@inputs:
    let
      forEachSystem = nixpkgs.lib.genAttrs (import systems);
    in
    {
      packages = forEachSystem (system: {
        devenv-up = self.devShells.${system}.default.config.procfileScript;
        devenv-test = self.devShells.${system}.default.config.test;
      });

      devShells = forEachSystem (
        system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        # llvm = pkgs.llvmPackages_latest;
        {
          default = devenv.lib.mkShell {
            inherit inputs pkgs;
            modules = [
              {
                env.VCPKG_ROOT = "${pkgs.vcpkg}/share/vcpkg";

                packages = [
                  # llvm.libllvm
                  # llvm.libstdcxxClang
                  # llvm.lldb
                  # (pkgs.clang-tools.override {enableLibcxx = true;})
                  pkgs.cmake
                  pkgs.cmake-format
                  pkgs.cmake-lint
                  pkgs.cppcheck
                  pkgs.flawfinder
                  pkgs.git
                  pkgs.vcpkg
                  pkgs.ninja
                  pkgs.gnumake
                  pkgs.gcc15
                ];

                languages = {
                  cplusplus.enable = true;
                  python = {
                    enable = true;
                    uv.enable = true;
                    package = pkgs.python313Full;
                  };
                  rust.enable = true;
                };

                pre-commit.hooks = {
                  # C++
                  clang-format = {
                    enable = true;
                    types_or = [
                      "c++"
                      "c"
                    ];
                  };
                  clang-tidy = {
                    enable = false;
                    types_or = [
                      "c++"
                      "c"
                    ];
                    entry = "clang-tidy -p build --fix";
                  };
                  # cppcheck = {
                  #   enable = true;
                  #   types = ["c++"];
                  #   entry = ''
                  #     cppcheck \
                  #         --check-level=exhaustive \
                  #         --enable=performance \
                  #         --enable=portability \
                  #         --enable=style \
                  #         --enable=warning \
                  #         --library=qt \
                  #         --error-exitcode=1 \
                  #         --inline-suppr \
                  #         --suppress=unusedStructMember \
                  #         --suppress=ctuOneDefinitionRuleViolation
                  #   '';
                  # };
                  flawfinder = {
                    enable = true;
                    pass_filenames = false;
                    entry = "flawfinder --error-level=0 ./src";
                  };

                  # CMake
                  cmake-format = {
                    enable = true;
                    types = [ "cmake" ];
                    entry = "cmake-format -c .cmake.yaml -i";
                  };
                  cmake-lint = {
                    enable = true;
                    types = [ "cmake" ];
                    entry = "cmake-lint -c .cmake.yaml";
                  };

                  # Python
                  ruff.enable = true;
                  ruff-format.enable = true;

                  # nix
                  nixfmt-rfc-style.enable = true;
                  deadnix.enable = true;
                  flake-checker.enable = true;
                  nil.enable = true;
                  statix.enable = true;

                  # toml
                  taplo.enable = true;
                  check-toml.enable = true;

                  # rust
                  cargo-check.enable = true;
                  cargo-verify-project = {
                    enable = true;
                    pass_filenames = false;
                    entry = "cargo verify-project --locked";
                  };
                  cargo-test = {
                    enable = true;
                    pass_filenames = false;
                    entry = "cargo test";
                  };
                  clippy.enable = true;
                  rustfmt.enable = true;
                };
              }
            ];
          };
        }
      );
    };
}
