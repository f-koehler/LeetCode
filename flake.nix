{
  description = "Fabian Koehler's LeetCode solutions (C++/Rust/Python)";

  inputs = {
    git-hooks = {
      url = "github:cachix/git-hooks.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    systems.url = "github:nix-systems/default";
  };

  outputs =
    { self, ... }@inputs:
    let
      forEachSystem = inputs.nixpkgs.lib.genAttrs (import inputs.systems);
      getNixpkgs =
        system:
        import inputs.nixpkgs {
          inherit system;
          config.allowUnfree = true;
        };

    in
    {
      checks = forEachSystem (system: {
        pre-commit-check = inputs.git-hooks.lib.${system}.run {
          src = ./.;
          hooks = {
            # nix
            deadnix.enable = true;
            flake-checker.enable = true;
            nil.enable = true;
            nixfmt-rfc-style.enable = true;
            statix.enable = true;

            # python
            ruff.enable = true;
            ruff-format.enable = true;

            # rust
            cargo-check.enable = true;
            clippy.enable = true;
            rustfmt.enable = true;

            # toml
            taplo.enable = true;

            # c++
            clang-format.enable = true;
            cmake-format.enable = true;
          };
        };
      });
      formatter = forEachSystem (
        system:
        let
          pkgs = getNixpkgs system;
          inherit (self.checks.${system}) pre-commit-check;
          script = ''
            ${pre-commit-check.config.package}/bin/pre-commit run --all-files --config ${pre-commit-check.config.configFile}
          '';
        in
        pkgs.writeShellScriptBin "pre-commit-run" script
      );
      devShells = forEachSystem (system: {
        default =
          let
            pkgs = getNixpkgs system;
            # inherit (inputs.nixpkgs) lib;
            inherit (self.checks.${system}) pre-commit-check;
          in
          pkgs.mkShell {
            buildInputs = pre-commit-check.enabledPackages;
            packages = [ ];
            env = { };
            inherit (pre-commit-check) shellHook;
          };
      });
    };
}
