{ *** uFMOD (OSS) unit for FreePascal *** }

unit uFMOD;

interface

{  function uFMOD_PlaySong(
      lpXM: Pointer;
      param, fdwSong: LongWord
   ): Pointer;
   ---
   Description:
   ---
      Loads the given XM song and starts playing it immediately,
      unless XM_SUSPENDED is specified. It will stop any currently
      playing song before loading the new one.
   ---
   Parameters:
   ---
     lpXM
        Specifies the song to play. If this parameter is 0, any
        currently playing song is stopped. In such a case, function
        does not return a meaningful value. fdwSong parameter
        determines whether this value is interpreted as a filename
        or as a pointer to an image of the song in memory.
     param
        If XM_MEMORY is specified, this parameter should be the size
        of the image of the song in memory.
        If XM_FILE is specified, this parameter is ignored.
     fdwSong
        Flags for playing the song. The following values are defined:
        XM_FILE      lpXM points to filename. param is ignored.
        XM_MEMORY    lpXM points to an image of a song in memory.
                     param is the image size. Once, uFMOD_PlaySong
                     returns, it's safe to free/discard the memory
                     buffer.
        XM_NOLOOP    An XM track plays repeatedly by default. Specify
                     this flag to play it only once.
        XM_SUSPENDED The XM track is loaded in a suspended state,
                     and will not play until the uFMOD_Resume function
                     is called. This is useful for preloading a song
                     or testing an XM track for validity.
  ---
  Return Values:
  ---
     On success, returns an OSS output device handle. Returns nil on
     failure. If you are familiar with OSS, you'll know what this
     handle might be useful for :)
  ---
  Remarks:
  ---
     If no valid song is specified and there is one currently being
     played, uFMOD_PlaySong just stops playback.
}
function uFMOD_PlaySong(lpXM:Pointer;param,fdwSong:LongWord):Pointer; cdecl; external name 'uFMOD_PlaySong';
procedure uFMOD_StopSong;

{  procedure uFMOD_Jump2Pattern(
      pat: LongWord
   );
   ---
   Description:
   ---
      Jumps to the specified pattern index.
   ---
   Parameters:
   ---
      pat
         Next zero based pattern index.
   ---
   Remarks:
   ---
      uFMOD doesn't automatically perform Note Off effects before jumping
      to the target pattern. In other words, the original pattern will
      remain in the mixer until it fades out. You can use this feature to
      your advantage. If you don't like it, just insert leading Note Off
      commands in all patterns intended to be used as uFMOD_Jump2Pattern
      targets.
      if the pattern index lays outside of the bounds of the pattern order
      table, calling this function jumps to pattern 0, effectively
      rewinding playback. }
procedure uFMOD_Jump2Pattern(pat:LongWord); cdecl; external name 'uFMOD_Jump2Pattern';
procedure uFMOD_Rewind;

{  procedure uFMOD_Pause;
   ---
   Description:
   ---
      Pauses the currently playing song, if any.
   ---
   Remarks:
   ---
      While paused you can still control the volume (uFMOD_SetVolume) and
      the pattern order (uFMOD_Jump2Pattern). The RMS volume coefficients
      (uFMOD_GetStats) will go down to 0 and the progress tracker
      (uFMOD_GetTime) will "freeze" while the song is paused.
      uFMOD_Pause doesn't perform the request immediately. Instead, it
      signals to pause when playback reaches next chunk of data, which may
      take up to about 40ms. This way, uFMOD_Pause performs asynchronously
      and returns very fast. It is not cumulative. So, calling
      uFMOD_Pause many times in a row has the same effect as calling it
      once. }
procedure uFMOD_Pause; external name 'uFMOD_Pause';

{  procedure uFMOD_Resume;
   ---
   Description:
   ---
      Resumes the currently paused song, if any.
   ---
   Remarks:
   ---
      uFMOD_Resume doesn't perform the request immediately. Instead, it
      signals to resume when an internal thread gets a time slice, which
      may take some milliseconds to happen. uFMOD_Resume is not
      cumulative. So, calling it many times in a row has the same effect
      as calling it once. }
procedure uFMOD_Resume; external name 'uFMOD_Resume';

{  function uFMOD_GetStats:LongWord;
   ---
   Description:
   ---
      Returns the current RMS volume coefficients in (L)eft and (R)ight
      channels.
         low-order word: RMS volume in R channel
         hi-order word:  RMS volume in L channel
      Range from 0 (silence) to $7FFF (maximum) on each channel.
   ---
   Remarks:
   ---
      This function is useful for updating a VU meter. It's recommended
      to rescale the output to log10 (decibels or dB for short), because
      human ears track volume changes in a dB scale. You may call
      uFMOD_GetStats() as often as you like, but take in mind that uFMOD
      updates both channel RMS volumes every 20-40ms, depending on the
      output sampling rate. So, calling uFMOD_GetStats about 16 times a
      second whould be quite enough to track volume changes very closely. }
function uFMOD_GetStats:LongWord; external name 'uFMOD_GetStats';

{  function uFMOD_GetRowOrder:LongWord;
   ---
   Description:
   ---
      Returns the currently playing row and order.
         low-order word: row
         hi-order word:  order
   ---
   Remarks:
   ---
      This function is useful for synchronization. uFMOD updates both
      row and order values every 20-40ms, depending on the output sampling
      rate. So, calling uFMOD_GetRowOrder about 16 times a second whould be
      quite enough to track row and order progress very closely. }
function uFMOD_GetRowOrder:LongWord; external name 'uFMOD_GetRowOrder';

{  function uFMOD_GetTime:LongWord;
   ---
   Description:
   ---
      Returns the time in milliseconds since the song was started.
   ---
   Remarks:
   ---
      This function is useful for synchronizing purposes. Multimedia
      applications can use uFMOD_GetTime to synchronize GFX to sound,
      for example. An XM player can use this function to update a
      progress meter. }
function uFMOD_GetTime:LongWord; external name 'uFMOD_GetTime';

{  function uFMOD_GetTitle:AnsiString;
   ---
   Description:
   ---
      Returns the current song's title.
   ---
   Remarks:
   ---
      Not every song has a title, so be prepared to get an empty string. }
function uFMOD_GetTitle:AnsiString; external name 'uFMOD_GetTitle';

{  procedure uFMOD_SetVolume(
      vol: LongWord
   );
   ---
   Description:
   ---
      Sets the global volume. The volume scale is linear.
   ---
   Parameters:
   ---
      vol
         New volume. Range: from uFMOD_MIN_VOL (muting) to uFMOD_MAX_VOL
         (maximum volume). Any value above uFMOD_MAX_VOL maps to maximum
         volume.
   ---
   Remarks:
   ---
      uFMOD internally converts the given values to a logarithmic scale (dB).
      Maximum volume is set by default. The volume value is preserved across
      uFMOD_PlaySong calls. You can set the desired volume level before
      actually starting to play a song. }
procedure uFMOD_SetVolume(vol:LongWord); cdecl; external name 'uFMOD_SetVolume';

const
	XM_MEMORY         = 1;
	XM_FILE           = 2;
	XM_NOLOOP         = 8;
	XM_SUSPENDED      = 16;
	uFMOD_MIN_VOL     = 0;
	uFMOD_MAX_VOL     = 25;
	uFMOD_DEFAULT_VOL = 25;

implementation

{$LinkLib ufmod}

procedure uFMOD_StopSong;
begin
	uFMOD_PlaySong(nil,0,0)
end;

procedure uFMOD_Rewind;
begin
	uFMOD_Jump2Pattern(0)
end;

end.
