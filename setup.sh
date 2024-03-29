#!/bin/bash

(

set -euo pipefail

cd $(dirname ${BASH_SOURCE[0]})

PKGDIR="$(readlink -f .)"
declare -i doPrintEnv=0
declare -i doPrintEnvInstr=0
declare -i needROOFITSYS_ROOTSYS=0
declare -a setupArgs=()

for farg in "$@"; do
  fargl="$(echo $farg | awk '{print tolower($0)}')"
  if [[ "$fargl" == "env" ]]; then
    doPrintEnv=1
  elif [[ "$fargl" == "envinstr" ]]; then
    doPrintEnvInstr=1
  else
    setupArgs+=( "$farg" ) 
  fi
done
declare -i nSetupArgs
nSetupArgs=${#setupArgs[@]}

printenv() {
  ../../MelaAnalytics/setup.sh env
  eval $(../../MelaAnalytics/setup.sh env)

  if [[ -d ../IvyDataTools ]]; then
    envopts="env"
    ../IvyDataTools/setup.sh ${envopts}
    eval $(../IvyDataTools/setup.sh ${envopts})
  fi

  libappend="${PKGDIR}/lib"
  end=""
  if [[ ! -z "${LD_LIBRARY_PATH+x}" ]]; then
    end=":${LD_LIBRARY_PATH}"
  fi
  if [[ "${end}" != *"$libappend"* ]]; then
    echo "export LD_LIBRARY_PATH=${libappend}${end}"
  fi
}
doenv() {
  eval $(../../MelaAnalytics/setup.sh env)

  if [[ -d ../IvyDataTools ]]; then
    envopts="env"
    eval $(../IvyDataTools/setup.sh ${envopts})
  fi
}
printenvinstr () {
  envopts="env"

  echo
  echo "remember to do"
  echo
  echo 'eval $('${BASH_SOURCE[0]}' '${envopts}')'
  echo "or"
  echo 'eval `'${BASH_SOURCE[0]}' '${envopts}'`'
  echo
  echo "if you are using a bash-related shell, or you can do"
  echo
  echo ${BASH_SOURCE[0]}' '${envopts}
  echo
  echo "and change the commands according to your shell in order to do something equivalent to set up the environment variables."
  echo
}

if [[ $doPrintEnv -eq 1 ]]; then
    printenv
    exit
elif [[ $doPrintEnvInstr -eq 1 ]]; then
    printenvinstr
    exit
fi

if [[ $nSetupArgs -eq 0 ]]; then
    setupArgs+=( -j 1 )
    nSetupArgs=2
fi


if [[ "$nSetupArgs" -eq 1 ]] && [[ "${setupArgs[0]}" == *"clean"* ]]; then
    make clean
    exit $?
elif [[ "$nSetupArgs" -ge 1 ]] && [[ "$nSetupArgs" -le 2 ]] && [[ "${setupArgs[0]}" == *"-j"* ]]; then
    : ok
else
    echo "Unknown arguments:"
    echo "  ${setupArgs[@]}"
    echo "Should be nothing, env, or clean"
    exit 1
fi

doenv

make "${setupArgs[@]}"
compile_status=$?
if [[ ${compile_status} -ne 0 ]]; then
  echo "Compilation failed with status ${compile_status}."
  exit ${compile_status}
fi

printenvinstr

)
