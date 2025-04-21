## Improve thread safety

Recorder and Player should be thread-safe.

## Improve error handling

MainInputProcessor should catch errors thrown in recorders and players.

## Add info component to ui

There should be an ui component 

## Use pub-sub for DeviceRepository.getPlayersInfo and getRecordersInfo

The methods should return a rxcpp::observable,
which allows observing the lists of PlayerInfos and RecorderInfos.

## Settings - tone workspace

Allow settings a folder as a workspace

## Settings - tone env variable

Allow setting a TONE_HOME env variable to point to a folder,
containing a settings file.

## Settings - folder aliases

Allow setting aliases for folders, which then can be used in the main input

## Main Input history

Store previously used commands, in memory and in a file, if TONE_HOME is set.

## Playlists

Provide functionality to create and use playlists.

## Create Release Build variant

Add a release cmake preset.

## Integrate Release Logger

Use release logger, when release variant is built.


