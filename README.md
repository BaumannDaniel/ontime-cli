# Project Description

**tone_cli** is a command line audio player and recorder.

# Manual

All functionality of the cli can be used via a set of commands.

## Commands

#### EXIT

Exit the program.

```
exit
```

#### ADD

Add a device for audio playback or recording.

*Subjects:*
- player
- recorder

```
add [subject] [file]

Example:
add player /music/test.mp3
add recorder /music/test.wav
```

#### START

Start a device by its id.

```
start [subject_id]

Example: start a
```

#### PLAY

Combines adding and starting a player.

```
play [file]

Example: play /music/test.mp3
```

#### STOP

Stop a device by its id.

```
stop [subject_id]

Example: stop a
```

#### REMOVE

Remove a device by its id.

```
remove [subject_id]

Example: remove a
```

#### FILE

Change the file of a device.

```
file [subject_id] [file]

Example: file a /music/another_test.mp3
```

# Build project

## Setup

For local development, add a **local.cmake** file.\
A template is available: **local_template.cmake**

## Build tone_cli

```
cmake --build --preset debug --target tone_cli
```

## Run Tests

```
cmake --build --preset debug
ctest --preset test-debug
```
