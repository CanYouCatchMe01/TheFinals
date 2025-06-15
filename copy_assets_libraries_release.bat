set output_dir=%~dp0x64\Release
set px_dll_path_dst=%~dp0TheFinals\physx\release\dll
robocopy "%~dp0Assets" "%output_dir%\Assets" /MIR
robocopy "%px_dll_path_dst%" "%output_dir%"