{
  description = "webdev starter";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils, ... }@inputs:
    utils.lib.eachDefaultSystem (
      system:
      let
        p = import nixpkgs { inherit system; };
      in
      {
        devShell = p.mkShell.override { stdenv = p.clangStdenv; } rec {
          packages = with p; [
            nodejs_22
            nodePackages.json-server
            nodePackages.vscode-langservers-extracted
            nodePackages.prettier

          ];
          name = "js";
        };
      }
    );
}

