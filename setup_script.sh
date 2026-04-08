#!/bin/bash

TASK=""
DEBUG_MODE=false
QUIET_MODE=false
OFFLINE_MODE=true

# 1. Parse Arguments
while [[ $# -gt 0 ]]; do
  case $1 in
    build|run|build-n-run)
      TASK="$1"
      shift
      ;;
    --debug)
      DEBUG_MODE=true
      shift # move to next argument
      ;;
    --quiet)
      QUIET_MODE=true
      shift
      ;;
    --offline)
      OFFLINE_MODE=true
      shift
      ;;
    *)
      echo "Unknown option: $1"
      exit 1
      ;;
  esac
done

# usage
if [ -z "$TASK" ]; then
    echo -e "Usage: [--debug] [--quiet] <build|run|build-n-run> "
    exit 1
fi

mkdir -p testInput testOutput

case "$TASK" in

    build)

        echo "--- Starting Image Build ---"
        docker $( [ "$DEBUG_MODE" = true ] && echo "--debug" ) build $( [ "$QUIET_MODE" = true ] && echo "--quiet" ) --progress=plain $( [ "$OFFLINE_MODE" = true ] && echo "--pull=false" ) -t offline-test-suite-image .
        ;;

    run)

        echo "--- Running Image in Container ---"
        case "$QUIET_MODE" in
            true)
                docker $( [ "$DEBUG_MODE" = true ] && echo "--debug" ) run --rm --network none -v $(pwd)/testInput:/ProjectDir/testInput -v $(pwd)/testOutput:/ProjectDir/testOutput -v $(pwd)/docker:/ProjectDir/scripts --name offline-test-suite-container offline-test-suite-image > ./testOutput/runtime_log.txt 2>&1
                ;;
            false)
                docker $( [ "$DEBUG_MODE" = true ] && echo "--debug" ) run --rm --network none -v $(pwd)/testInput:/ProjectDir/testInput -v $(pwd)/testOutput:/ProjectDir/testOutput -v $(pwd)/docker:/ProjectDir/scripts --name offline-test-suite-container offline-test-suite-image
                ;;
        esac
        ;;

    build-n-run)

        echo "--- Building Image then Running Container ---"
        echo "1. build"
        docker $( [ "$DEBUG_MODE" = true ] && echo "--debug" ) build $( [ "$QUIET_MODE" = true ] && echo "--quiet" ) --progress=plain $( [ "$OFFLINE_MODE" = true ] && echo "--pull=false" ) -t offline-test-suite-image .
        echo "2. run"
        case "$QUIET_MODE" in
            true)
                docker $( [ "$DEBUG_MODE" = true ] && echo "--debug" ) run --rm --network none -v $(pwd)/testInput:/ProjectDir/testInput -v $(pwd)/testOutput:/ProjectDir/testOutput -v $(pwd)/docker:/ProjectDir/scripts --name offline-test-suite-container offline-test-suite-image > ./testOutput/runtime_log.txt 2>&1
                ;;
            false)
                docker $( [ "$DEBUG_MODE" = true ] && echo "--debug" ) run --rm --network none -v $(pwd)/testInput:/ProjectDir/testInput -v $(pwd)/testOutput:/ProjectDir/testOutput -v $(pwd)/docker:/ProjectDir/scripts --name offline-test-suite-container offline-test-suite-image
                ;;
        esac
        ;;
    *)

        echo "Error: Unknown command '$TASK'"
        exit 1
        ;;
esac

echo "CLI finished"