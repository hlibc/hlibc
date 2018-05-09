{ pkgs ? (import <nixpkgs> {})
, stdenv ? pkgs.stdenv
, gnumake ? pkgs.gnumake
}:

stdenv.mkDerivation rec {
  name = "hlibc";
  version = "0.0.1";

  src = ./../..;

  phases = [ "unpackPhase" "patchPhase" "checkPhase" "configurePhase" "installPhase" ];
  checkPhase = ''
    echo $NIX_BUILD_CORES
    export CFLAGS="-g"; make gcctest -j$NIX_BUILD_CORES
  '';

  doCheck = true;

  hardeningDisable = ["all"];

  buildInputs = [ gnumake ];
}
