# Repository architecture

Repository architecture is as follows:

- /.github: github workflow directory for automated tests,
- /docker: contains the main script and the python venv requirements
- /docs: documentation directory,
- /target: directory for target source code: UFiT
- /testSuite:
    - /testSuite/frameworks: testing frameworks local clone,
    - /testSuite/testOutput: output of the docker container,
    - /testSuite/tests: the unit tests directory
