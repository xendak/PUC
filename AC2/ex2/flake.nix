{
  description = "Ambiente de desenvolvimento para atividade de Arquitetura de Computadores";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils"; # Adiciona o flake-utils
  };

  # A saída agora usa o flake-utils para gerar a configuração para cada sistema
  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        # Define os pacotes Python que queremos no ambiente
        pythonPackages =
          ps: with ps; [
            pandas # Ótimo para manipulação de dados e análise dos CSVs
            matplotlib # Essencial para plotar gráficos
            seaborn # Facilita a criação de gráficos estatísticos bonitos
          ];

        pythonWithPackages = pkgs.python3.withPackages pythonPackages;
      in
      {
        devShells.default = pkgs.mkShell {
          name = "arqcomp-env";

          # Pacotes que estarão disponíveis no shell
          buildInputs = [
            pkgs.gcc # O compilador C
            pythonWithPackages # Python com as bibliotecas de análise
          ];

          # Mensagem que aparece ao entrar no ambiente
          shellHook = ''
            echo "Ambiente de Arquitetura de Computadores ativado! 🚀"
            echo "Ferramentas disponíveis: gcc, python"
            echo "Use 'python gerar_dados.py' para coletar os dados."
          '';
        };
      }
    );
}
