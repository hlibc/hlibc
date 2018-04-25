{ pkgs ? (import <nixpkgs> {})
, stdenv ? pkgs.stdenv
, gnumake ? pkgs.gnumake
}:

stdenv.mkDerivation rec {
  name = "hlibc";
  version = "0.0.1";

  src = ./.;

  phases = [ "unpackPhase" "checkPhase" "configurePhase" "installPhase" ];
  preCheckPhase = ''
    export ARCH=${pkgs.stdenv.targetPlatform.platform.kernelArch}
  '';
  checkPhase = ''
    make gcctest
  '';

  doCheck = true;


  hardeningDisable = ["all"];

  buildInputs = [ gnumake ];
}
