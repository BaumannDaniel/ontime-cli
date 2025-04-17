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

Add a player for audio playback.

```
add [subject] [file]

Example: add player /music/test.mp3
```

#### START

Start a player by its id.

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

Stop a player by its id.

```
stop [subject_id]

Example: stop a
```

#### REMOVE

Remove a player by its id.

```
remove [subject_id]

Example: remove a
```

#### FILE

Change the file of a player.

```
file [subject_id] [file]

Example: file a /music/another_test.mp3
```

# Build project

```
cmake --build --preset debug --target tone_cli
```

## Run Tests

```
cmake --build --preset debug
ctest --preset test-debug
```
