{
  description = "A generic development shell";

  # To update flake.lock to the latest nixpkgs: `nix flake update`
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  # output format guide https://nixos.wiki/wiki/Flakes#Output_schema
  outputs = { self, nixpkgs }: let 
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.${system} = {
      # is updated to the latest gcc on `nix flake update`
      # doc: https://nixos.org/manual/nixpkgs/stable/#sec-pkgs-mkShell
      default = pkgs.mkShell {
        buildInputs = with pkgs; [ # also called `buildInputs`
          # manually found (some used to be installed by random scripts)
          wrk
          nginx

          # from run.sh
          #git
          #clang
          #bsdcpio # not in nixpkgs. Maybe try gnu pkgs.cpio
          doxygen
          libhugetlbfs
          #build-essential # whatever. maybe later
          qemu
          redis # actually redis-tools, but maybe this is enough
          socat
          meson
          cscope
          libseccomp # -dev
          #uuid-runtime # what even is this
          cloc
          #uuid-dev # probably not needed
          libuuid # actually libuuid1
          bridge-utils
          nettools
          #ifupdown # we surely need this
          bison
          #curl
          flex
          #wget
          #sudo
          #libmhash-dev
          libmhash # actually libmhash2
          #linux-cpupower # whatever
          gawk
          #musl-tools
          qemu-utils
          # plot script requirements from run.sh omitted
        ];

        # All assignments become environments variable in the development shell.
        SOME_ENV_VAR = "bar";
      };

      # Pinned gcc: remain on gcc10 even after `nix flake update`
      #default = pkgs.mkShell.override { stdenv = pkgs.gcc10Stdenv; } {
      #  depsBuildHost = with pkgs; [
      #    cmake pkg-config
      #  ];
      #  depsHostTarget = with pkgs; [
      #    zlib
      #  ];
      #};

      # Clang example:
      #default = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } {
      #  depsBuildHost = with pkgs; [
      #    cmake pkg-config
      #  ];
      #  depsHostTarget = with pkgs; [
      #    zlib
      #  ];
      #};
    };
  };
}
