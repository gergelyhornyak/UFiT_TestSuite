# Setup

How to setup the test suite?

1. Clone this repository
2. Have docker and docker-compose installed: `(sudo) apt-get install docker docker.io docker-compose`
3. run `(sudo) docker compose up (--build)` 
    sudo    if not superuser
    --build if you want to rebuild the base image
    usually takes around 10m 58s
5. You should see the logs in the command line, or
6. Check them using `(sudo) docker logs testSuiteContainer`
7. You should find the results in the /outputs directory
