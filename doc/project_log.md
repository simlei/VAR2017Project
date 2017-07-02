# Project log

This documents the progress, organization and remaining work. This document was
started on June 19th 2017, at a state where the project seemed to slow down a
little, in an effort to organize things better and to introduce a sense of urgency.

## Project inception - from April 24 to May 8

- Research and project pitch for the initial VAR Project kick-off
- [Original pitch](project_pitch.md)
- The project (in the scope of the VAR class 2017) in a nutshell:
  _A programm/app which tracks the guitar playing
  of the user visually and musically, offering optical support and lessons
  using augmented reality techniques_
- The big idea in a nutshell: _Provide a stable framework that allows recording
  of and experimenting with musical data, including aligning different streams
  of data in a single reference frame (e. g.: a song). The intention is to later
  be able to infer the data that was formerly recorded directly from sensors
  (e. g: instead of a electronically augmented guitar, use a regular one without
  electronics attached)_
- Musical tracking solely by listening to the audio was already recognized as
  too difficult following the discussion in the literature that turned up
  during research
- Recognition of the guitar fretboard without markers seemed possible at the time, but
  we decided very early in favor of using simple ARuCo Markers first due to them
  having the better cost/benefit trade-off by far for the start of the project
- Tracking of the human hand was a big idea then, but now considered to be, if at all, only a thing for a very late stage of the project (e. g. when the electrically modified guitar is ditched)

# May 8 - May 22

 - Project pitch happened
 - Tim Unverzagt joined the project!
 - Experimentation with Unity + Vuforia for the graphical frontent and optical tracking, conclusion that we rather not use that (too much configuration by GUI and Wizards)
 - Research into the [CLAM project](http://clam-project.org/), a library and also
 framework to analyze, visualize, organize streams of musical data (inactive since 2011, but quite promising)
 - Research into hardware required to build something resembling the [OpenChord V1
 guitar](http://www.laboratoryspokane.com/openchord/the-openchord-v1-guitar/)
 as proposed in the project pitch

## May 22 - June 12
- Research into alternatives to Unity/Vuforia brought us to
  [OpenFrameworks](http://openframeworks.cc) (_"... is an open source C++ toolkit for creative coding"_), a C++ based framework giving easy access to community libraries, simplifying OpenGL and external hardware access. Despite being beginner-friendly, it's 100% code in contrast to Unity/Vuforia.
- Adaptation of OpenFrameworks for our project
- Switching platform from Windows 10 to Ubuntu 16.04
- Implementation of first optical ARuCo marker/guitar tracking in an OpenFrameworks project
- Display of static markers on a sudo guitar fretboard
- Acquisition of cheap electrical guitar (Fender Squire Strat model) as basis for the electrically augmented guitar

## June 12 - ???

- Acquisition of materials ad plan for building the electrically augmented guitar
- --- link
- Documentation (hic)
- Principled optical tracking of the guitar position in space implemented
- Code cleanup  
- Organization: Splitting workloads into two tracks:
   * Frontend / Teaching GUI / ARuCo tracking
   * Electronics / musical modelling / data/backend support

As of this date, we have spent 6 weeks trying out frameworks and implementing a
proof-of-concept optical tracking application.
