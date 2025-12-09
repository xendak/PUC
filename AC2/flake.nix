{
  description = "Venus RISC-V Simulator";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      utils,
      ...
    }:
    utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in
      {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "venus";
          version = "2.1.0";

          src = ./.;

          nativeBuildInputs = with pkgs; [
            gradle
            jdk17
            makeWrapper
          ];

          buildPhase = ''
            export GRADLE_USER_HOME=$(mktemp -d)
            gradle shadowJar --no-daemon --offline || gradle shadowJar --no-daemon
          '';

          installPhase = ''
            mkdir -p $out/bin $out/lib

            # Find the generated jar file
            jarfile=$(find build/libs -name "venus-*.jar" -type f | head -n1)

            if [ -z "$jarfile" ]; then
              echo "Error: Could not find venus jar file"
              exit 1
            fi

            cp "$jarfile" $out/lib/venus.jar

            # Create wrapper script
            makeWrapper ${pkgs.jdk17}/bin/java $out/bin/venus \
              --add-flags "-jar $out/lib/venus.jar"
          '';

          meta = with pkgs.lib; {
            description = "Venus RISC-V simulator";
            homepage = "https://github.com/61c-teach/venus";
            license = licenses.mit;
            platforms = platforms.all;
            mainProgram = "venus";
          };
        };

        # Development shell
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            gradle
            jdk17
          ];

          shellHook = ''
            echo "Venus RISC-V Simulator dev environment"
            echo "Run 'gradle build' to build the project"
            echo "Run 'gradle shadowJar' to create a fat JAR"
          '';
        };
      }
    );
}
