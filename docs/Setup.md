# Setup

How to setup the test suite?

1. Clone this repository
2. Have docker installed: `(sudo) apt-get install docker docker.io`
3. `docker build --progress=plain -t <image_name> .`
4. `docker --debug run --rm -v $(pwd)/testInput:/ProjectDir/testInput -v $(pwd)/testOutput:/ProjectDir/testOutput --name <container_name> <image_name>` 
5. You should see the logs in the command line, or can inspect them with `docker logs -f <container_name>`
6. After test suite is finished, you should find the results in the /testOutput directory

*Step 4* ensures the reusability of the docker image built in *Step 3*. After building the base image, the container will read the input files every time its run. Additionally *Step 4* automatically removes the container and its associated anonymous volumes when it exits.