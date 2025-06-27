# Roadmap

Roadmap of the Test Suite Development Project

## Research, Plan and Setup

Identify critical components of the UFiT program to be tested, and areas that require optimization. Research interoperability between Fortran90 C++. Setup the system: whether to use containerisation, Windows/Linux/iOS, third-party softwares, etc.

## Investigating State-of-the-Art Testing Frameworks

Evaluate modern C++ testing frameworks such as Google Test, Catch2, and Boost-Test. Compare features like usability, compatibility, CI/CD support, and performance. Finalize the choice of the testing framework for the project.

## Planning the Test Suite

Design the structure of the test suite, including unit testing, integration testing, and benchmarking. Develop a test plan to cover UFiT’s core functionalities. Define metrics for benchmarking and optimization evaluation. \n
[OPTIONAL] Create a CI/CD pipeline plan for testing automation. Automate the test execution.

Set up the development environment for C++ testing with the chosen framework and ensure smooth integration between the C++ test suite and the Fortran (F90) components.

## Development of Unit Tests

Write unit tests for UFiT’s critical functions (e.g., fieldline tracing algorithms, input/output modules). Verify the correctness, reliability, and accuracy of UFiT through test cases.

## Benchmarking and Performance Testing

Identify bottlenecks in UFiT’s performance and document findings. Implement benchmarking tests to measure and evaluate UFiT’s computational performance.

## Review

Refactor the test suite to ensure maintainability, scalability, and readability. Optimize the CI/CD pipeline to reduce build and testing times. Validate test suite compatibility with UFiT’s current and future development needs.

### Conduct a comprehensive assessment of the test suite’s effectiveness.

Analyze how much of the UFiT codebase is covered by the test suite.
Use tools like gcov or lcov

Conduct a review session with project supervisor and gather feedback on usability and relevance.
Verify that developers can easily run, debug, and extend the test suite without excessive onboarding time.

Finish detailed documentation for the test suite

#### Validate that false positives and false negatives are minimized by refining test conditions.

If the code is broken, but the test passes; that is a false positive.
If the code is correct, but the test fails; that is a false negative.
If the code is correct and the test passes; that is a true  positive.
If the code is broken and the test fails,   that is a true  negative.

Document how performance changes based on varying workloads or input sizes.

Identify areas where test execution can be optimized without sacrificing reliability (e.g., parallelizing test execution).

[OPTIONAL] Assess how well the pipeline handles growing codebases, additional test cases, and increasing complexity.

Run the test suite repeatedly under different conditions (e.g., varying environments, hardware configurations) to ensure consistent results.
Identify any flaky tests that might provide inconsistent outcomes and address their underlying issues.
