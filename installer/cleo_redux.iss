#define AppName "CLEO Redux"
#define AppVersion "1.2.0"
#define AppPublisher "Seemann"
#define AppURL "https://re.cleo.li"
#define SourceDir "..\"
#define OutputDir "build"

#define UAL64 = "https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/x64-latest"
#define UAL32 = "https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/Win32-latest"

#define ImGuiRedux32 = "https://github.com/user-grinch/ImGuiRedux/releases/download/Win32-latest"
#define ImGuiRedux64 = "https://github.com/user-grinch/ImGuiRedux/releases/download/Win64-latest"

#define SilentPatchIII = "https://silent.rockstarvision.com/uploads/SilentPatchIII.zip"
#define SilentPatchVC = "https://silent.rockstarvision.com/uploads/SilentPatchVC.zip"
#define SilentPatchSA = "https://silent.rockstarvision.com/uploads/SilentPatchSA.zip"

#define MemOps32 = "https://github.com/cleolibrary/CLEO-REDUX-PLUGINS/releases/download/latest/MemoryOperations.zip"
#define MemOps64 = "https://github.com/cleolibrary/CLEO-REDUX-PLUGINS/releases/download/latest/MemoryOperations64.zip"

[Setup]
AppId={{511AFCDA-FD5E-491C-A1B7-22BAC8F93711}
AppName={#AppName}
AppVersion={#AppVersion}
VersionInfoVersion={#AppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#AppPublisher}
AppPublisherURL={#AppURL}
AppCopyright=Copyright (c) 2021-2023, {#AppPublisher}
DefaultDirName=New folder
LicenseFile={#SourceDir}\LICENSE.txt
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
;PrivilegesRequiredOverridesAllowed=dialog
OutputDir={#OutputDir}
OutputBaseFilename=cleo_redux_setup
SetupIconFile=cr4.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern
AppendDefaultDirName=false
DirExistsWarning=false
EnableDirDoesntExistWarning=true
UsePreviousAppDir=no
Uninstallable=false

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"; LicenseFile: "..\LICENSE-RU.txt"

[Types]
Name: "full"; Description: "Full"; Flags: iscustom

[Components]
Name: "program"; Description: "CLEO Redux"; Types: full; Flags: fixed
Name: "program/commands"; Description: "API files (unselect if you prefer to download the latest API files during the first game run)"; Types: full;
Name: "plugins"; Description: "Extensions"; Types: full
Name: "plugins/ini"; Description: "IniFiles 1.2"; Types: full
Name: "plugins/dylib"; Description: "Dylib 1.1"; Types: full
Name: "plugins/imgui"; Description: "ImGuiRedux (by Grinch_)"; Types: full
Name: "plugins/imgui/d3d8to9"; Description: "d3d8to9 Wrapper - for games using DirectX 8"; Types: full
Name: "plugins/imgui/SilentPatch"; Description: "SilentPatch - needed for the mouse to work properly in classic GTA"; Types: full
Name: "plugins/memops"; Description: "MemoryOperations (by ThirteenAG)"; Types: full
Name: "plugins/input"; Description: "Input 1.3"; Types: full
Name: "plugins/frontend"; Description: "Frontend 1.1"; Types: full
Name: "plugins/events"; Description: "Events 1.1"; Types: full
Name: "loaders"; Description: "File Loaders"; Types: full
Name: "loaders/text"; Description: "*.txt, *.text (Text files)"; Types: full
Name: "loaders/ide"; Description: "*.ide (Item Definition files)"; Types: full

Name: "asiloader"; Description: "Ultimate ASI Loader (by ThirteenAG)"; Types: full

[Dirs]
Name: "{app}"; Permissions: users-modify
Name: "{app}\CLEO"; Permissions: users-modify

[Files]
; CLEO
Source: "{#SourceDir}\cleo_redux.asi"; DestDir: "{app}"; Flags: ignoreversion; Check: IsX86;  Components: program;
Source: "{#SourceDir}\cleo_redux64.asi"; DestDir: "{app}"; Flags: ignoreversion; Check: IsX64;  Components: program;

; SDK
Source: "{#OutputDir}\unknown_x86\CLEO\.config\unknown_x86.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsX86;  Components: program/commands;
Source: "{#OutputDir}\unknown_x86\CLEO\.config\unknown_x86.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsX86; Components: program/commands;
Source: "{#OutputDir}\unknown_x86\CLEO\.config\unknown.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsX86; Components: program/commands;
Source: "{#OutputDir}\unknown_x64\CLEO\.config\unknown_x64.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsX64;  Components: program/commands;
Source: "{#OutputDir}\unknown_x64\CLEO\.config\unknown_x64.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsX64; Components: program/commands;
Source: "{#OutputDir}\unknown_x64\CLEO\.config\unknown.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsX64; Components: program/commands;

; unknown x86
Source: "{#OutputDir}\unknown_x86\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsUnknown and IsX86;  Components: program/commands;
; unknown x64
Source: "{#OutputDir}\unknown_x64\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsUnknown and IsX64;  Components: program/commands;
; GTA III and re3
Source: "{#OutputDir}\gta3\CLEO\.config\gta3.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsGta3;  Components: program/commands;
Source: "{#OutputDir}\gta3\CLEO\.config\gta3.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsGta3;  Components: program/commands;
Source: "{#OutputDir}\gta3\CLEO\.config\gta3.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsGta3;  Components: program/commands;
Source: "{#OutputDir}\gta3\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsGta3;  Components: program/commands;
; GTA VC and reVC
Source: "{#OutputDir}\vc\CLEO\.config\vc.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsVC;  Components: program/commands;
Source: "{#OutputDir}\vc\CLEO\.config\vc.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsVC;  Components: program/commands;
Source: "{#OutputDir}\vc\CLEO\.config\vc.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsVC;  Components: program/commands;
Source: "{#OutputDir}\vc\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsVC;  Components: program/commands;
; GTA SA
Source: "{#OutputDir}\sa\CLEO\.config\sa.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsSA;  Components: program/commands;
Source: "{#OutputDir}\sa\CLEO\.config\sa.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsSA;  Components: program/commands;
Source: "{#OutputDir}\sa\CLEO\.config\sa.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsSA;  Components: program/commands;
Source: "{#OutputDir}\sa\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsSA;  Components: program/commands;
; GTA IV
Source: "{#OutputDir}\gta_iv\CLEO\.config\gta_iv.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsIV;  Components: program/commands;
Source: "{#OutputDir}\gta_iv\CLEO\.config\gta_iv.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsIV;  Components: program/commands;
Source: "{#OutputDir}\gta_iv\CLEO\.config\gta_iv.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsIV;  Components: program/commands;
Source: "{#OutputDir}\gta_iv\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsIV;  Components: program/commands;
; GTA III Unreal
Source: "{#OutputDir}\gta3_unreal\CLEO\.config\gta3_unreal.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: Is3Master;  Components: program/commands;
Source: "{#OutputDir}\gta3_unreal\CLEO\.config\gta3_unreal.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: Is3Master;  Components: program/commands;
Source: "{#OutputDir}\gta3_unreal\CLEO\.config\gta3.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: Is3Master;  Components: program/commands;
Source: "{#OutputDir}\gta3_unreal\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: Is3Master;  Components: program/commands;
; GTA VC Unreal
Source: "{#OutputDir}\vc_unreal\CLEO\.config\vc_unreal.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsVCMaster;  Components: program/commands;
Source: "{#OutputDir}\vc_unreal\CLEO\.config\vc_unreal.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsVCMaster;  Components: program/commands;
Source: "{#OutputDir}\vc_unreal\CLEO\.config\vc.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsVCMaster;  Components: program/commands;
Source: "{#OutputDir}\vc_unreal\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsVCMaster;  Components: program/commands;
; GTA SA Unreal
Source: "{#OutputDir}\sa_unreal\CLEO\.config\sa_unreal.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsSAMaster;  Components: program/commands;
Source: "{#OutputDir}\sa_unreal\CLEO\.config\sa_unreal.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsSAMaster;  Components: program/commands;
Source: "{#OutputDir}\sa_unreal\CLEO\.config\sa.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsSAMaster;  Components: program/commands;
Source: "{#OutputDir}\sa_unreal\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsSAMaster;  Components: program/commands;
; Bully
Source: "{#OutputDir}\bully\CLEO\.config\bully.json"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsBully;  Components: program/commands;
Source: "{#OutputDir}\bully\CLEO\.config\bully.enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsBully;  Components: program/commands;
Source: "{#OutputDir}\bully\CLEO\.config\bully.d.ts"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsBully;  Components: program/commands;
Source: "{#OutputDir}\bully\CLEO\.config\enums.js"; DestDir: "{app}\CLEO\.config"; Flags: ignoreversion; Check: IsBully;  Components: program/commands;

; Source: "{#SourceDir}\Release\LICENSE.txt"; DestDir: "{app}"; DestName: "CLEO_REDUX_LICENSE.txt"; Flags: ignoreversion;  Components: program

; UAL
; x86
Source: "{tmp}\dinput8.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: (isGTA3 or IsVC or isIV) and IsX86; AfterInstall: Extract('{app}\dinput8.zip', 'dinput8.dll', '{app}');  Components: asiloader;
Source: "{tmp}\vorbisFile.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: not isGTA3 and not isVC and not isIV and IsX86; AfterInstall: Extract('{app}\vorbisFile.zip', 'vorbisFile.dll', '{app}');  Components: asiloader;
; x64
Source: "{tmp}\d3d9.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: isRe and IsX64; AfterInstall: Extract('{app}\d3d9.zip', 'd3d9.dll', '{app}');  Components: asiloader;
Source: "{tmp}\version.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: not isRe and IsX64; AfterInstall: Extract('{app}\version.zip', 'version.dll', '{app}');  Components: asiloader;

; Plugins
Source: "{#SourceDir}\plugins\Dylib\build\dylib.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: plugins/dylib
Source: "{#SourceDir}\plugins\Dylib\build\dylib64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: plugins/dylib
Source: "{#SourceDir}\plugins\IniFiles\build\IniFiles.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: plugins/ini
Source: "{#SourceDir}\plugins\IniFiles\build\IniFiles64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: plugins/ini
Source: "{#SourceDir}\plugins\Input\build\Input.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: plugins/input
Source: "{#SourceDir}\plugins\Input\build\Input64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: plugins/input
Source: "{#SourceDir}\plugins\Frontend\Frontend.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86 and (IsGta3 or IsVC or IsSA); Components: plugins/frontend
Source: "{#SourceDir}\plugins\Events\build\Events.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86 and not IsUnknown; Components: plugins/events
Source: "{#SourceDir}\plugins\Events\build\Events64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64 and not IsUnknown; Components: plugins/events

Source: "{tmp}\ImGuiRedux.zip"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: deleteafterinstall external; Check: IsX86; AfterInstall: InstallImGuiRedux32; Components: plugins/imgui;
Source: "{tmp}\ImGuiRedux.zip"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: deleteafterinstall external; Check: IsX64; AfterInstall: Extract('{app}\CLEO\CLEO_PLUGINS\ImGuiRedux.zip', 'ImGuiReduxWin64.cleo', '{app}\CLEO\CLEO_PLUGINS'); Components: plugins/imgui;

Source: "{tmp}\d3d8.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; AfterInstall: Extract('{app}\d3d8.zip', 'd3d8.dll', '{app}'); Components: plugins/imgui/d3d8to9;
Source: "{tmp}\SilentPatch.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; AfterInstall: ExtractAll('{app}\SilentPatch.zip', '{app}'); Components: plugins/imgui/SilentPatch;

Source: "{tmp}\MemoryOperations.zip"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: deleteafterinstall external; Check: IsX86; AfterInstall: Extract('{app}\CLEO\CLEO_PLUGINS\MemoryOperations.zip', 'MemoryOperations.cleo', '{app}\CLEO\CLEO_PLUGINS'); Components: plugins/memops;
Source: "{tmp}\MemoryOperations.zip"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: deleteafterinstall external; Check: IsX64; AfterInstall: Extract('{app}\CLEO\CLEO_PLUGINS\MemoryOperations.zip', 'MemoryOperations64.cleo', '{app}\CLEO\CLEO_PLUGINS'); Components: plugins/memops;


; Custom File Loaders
Source: "{#SourceDir}\loaders\TextLoader\build\TextLoader.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: loaders/text
Source: "{#SourceDir}\loaders\TextLoader\build\TextLoader64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: loaders/text
Source: "{#SourceDir}\loaders\IdeLoader\build\IdeLoader.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: loaders/ide
Source: "{#SourceDir}\loaders\IdeLoader\build\IdeLoader64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: loaders/ide

[INI]
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "General"; Key: "AllowCs"; String: 1
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "General"; Key: "AllowJs"; String: 1
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "General"; Key: "AllowFxt"; String: 1
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "General"; Key: "LogOpcodes"; String: 0
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "General"; Key: "PermissionLevel"; String: Lax

; will be set in wpFinished
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "Host"; Key: "EnableSelfHost"; String: 0 
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "Host"; Key: "SelfHostFps"; String: 30

Filename: "{app}\CLEO\.config\cleo.ini"; Section: "Permissions"; Key: "mem"; String: 1
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "Permissions"; Key: "dll"; String: 1
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "Permissions"; Key: "fs"; String: 0
Filename: "{app}\CLEO\.config\cleo.ini"; Section: "Permissions"; Key: "net"; String: 0


[CustomMessages]
m2 =Select CLEO Redux version
m3 =Which version of CLEO Redux (32-bit or 64-bit) should be installed?
m4 =No supported game or application was found in the selected directory. To continue installation select either one of the two available versions of CLEO Redux. Hint: it should match the version (architecture) of the target game or application that will run CLEO Redux.
m5 =32-bit (x86)
m6 =64-bit (x64)
m7 =Automatically run as self-host
m8 =CLEO Redux supports both 32-bit and 64-bit versions of re3 and reVC. To continue installation select either one of the two available versions of CLEO Redux.

russian.m2 =Выберите версию CLEO Redux
russian.m3 =Какую версию CLEO Redux (32-битную или 64-битную) нужно установить?
russian.m4 =В выбранной директории не нашлось поддерживаемых игр или приложений. Для продолжения установки выберите одну из двух возможных версий CLEO Redux. Подсказка: она должна совпадать с версией (архитектурой) игры или приложения, в которой будет запускаться CLEO Redux.
russian.m5 =32-битная (x86)
russian.m6 =64-битная (x64)
russian.m7 =Автоматически запускать в автономном режиме
russian.m8 =CLEO Redux поддерживает как 32-битные, так и 64-битные версии re3 и reVC. Для продолжения установки выберите одну из двух возможных версий CLEO Redux.
           
[Code]
const
  SHCONTCH_NOPROGRESSBOX = 4;
  SHCONTCH_RESPONDYESTOALL = 16;

var
  FIsX64: Boolean;
  FGameId: Integer;
  DownloadPage: TDownloadWizardPage;
  ArchPage, ReArchPage: TInputOptionWizardPage;
  DefaultDirOnce: Boolean;
  EnableSelfHostCb: TNewCheckBox;

function IsX64(): Boolean;
begin
  Result := FIsX64 or ArchPage.Values[1] or ReArchPage.Values[1];
end;

function IsX86(): Boolean;
begin
  Result := not IsX64();
end;

function NeedsD3Wrapper(): Boolean;
begin
  Result := (FGameId in [0, 1, 2, 3, 4, 10]);
end;

function NeedsSilentPatch(): Boolean;
begin
  Result := (FGameId in [3, 4, 5]);
end;

function SupportsFrontend(): Boolean;
begin
  Result := (FGameId in [1, 2, 3, 4, 5]);
end;

procedure unzipFile(Src, FileName, TargetFldr: PAnsiChar);
var
  Shell: variant;
  Item: variant;
  SrcFldr, DestFldr: variant;
begin
  if FileExists(Src) then 
  begin
    ForceDirectories(TargetFldr);

    Shell := CreateOleObject('Shell.Application');

    SrcFldr := Shell.NameSpace(string(Src));
    DestFldr := Shell.NameSpace(string(TargetFldr));
    Item := SrcFldr.ParseName(FileName);

    if not VarIsClear(Item) then
      DestFldr.CopyHere(Item, SHCONTCH_NOPROGRESSBOX or SHCONTCH_RESPONDYESTOALL);
 
  end;
end;

procedure unzipFolder(Src, TargetFldr: PAnsiChar);
var
  Shell: variant;
  SrcFldr, DestFldr: variant;
begin
  if FileExists(Src) then 
  begin
    ForceDirectories(TargetFldr);

    Shell := CreateOleObject('Shell.Application');

    SrcFldr := Shell.NameSpace(string(Src));
    DestFldr := Shell.NameSpace(string(TargetFldr));
    
    DestFldr.CopyHere(SrcFldr.Items, SHCONTCH_NOPROGRESSBOX or SHCONTCH_RESPONDYESTOALL);
 
  end;
end;

procedure Extract(Src, FileName, Target : String);
begin
  unzipFile(ExpandConstant(Src), ExpandConstant(FileName), ExpandConstant(target));
end;

procedure ExtractAll(Src, Target : String);
begin
  unzipFolder(ExpandConstant(Src), ExpandConstant(target));
end;

function GetSilentPatchName(): String;
begin
  if FGameId = 3 then 
    Result := 'SilentPatchIII.asi'
  else if FGameId = 4 then 
    Result := 'SilentPatchVC.asi'
  else if FGameId = 5 then 
    Result := 'SilentPatchSA.asi';
end;

procedure InstallImGuiRedux32();
begin
  Extract('{app}\CLEO\CLEO_PLUGINS\ImGuiRedux.zip', 'ImGuiReduxWin32.cleo', '{app}\CLEO\CLEO_PLUGINS');
  DeleteFile(ExpandConstant('{app}\CLEO\CLEO_PLUGINS\ImGuiRedux.cleo'));
end;

function IdentifyGame(Dir: String): Integer;
begin
  if FileExists(Dir + '\re3.exe') then
  begin
    Result := 1;
    Exit;
  end;
  if FileExists(Dir + '\revc.exe') then
  begin
    Result := 2;
    Exit;
  end;
  if FileExists(Dir + '\gta3.exe') then
  begin
    Result := 3;
    FIsX64 := False;
    Exit;
  end;
  if FileExists(Dir + '\gta-vc.exe') then
  begin
    Result := 4;
    FIsX64 := False;
    Exit;
  end;
  if FileExists(Dir + '\gta_sa.exe') or FileExists(Dir + '\gta-sa.exe') or FileExists(Dir + '\gta_sa_compact.exe') then
  begin
    Result := 5;
    FIsX64 := False;
    Exit;
  end;
  if FileExists(Dir + '\libertycity.exe') then
  begin
    Result := 6;
    FIsX64 := True;
    Exit;
  end;
  if FileExists(Dir + '\vicecity.exe') then
  begin
    Result := 7;
    FIsX64 := True;
    Exit;
  end;
  if FileExists(Dir + '\sanandreas.exe') then
  begin
    Result := 8;
    FIsX64 := True;
    Exit;
  end;
  if FileExists(Dir + '\GTAIV.exe') then
  begin
    Result := 9;
    FIsX64 := False;
    Exit;
  end;
  if FileExists(Dir + '\bully.exe') then
  begin
    Result := 10;
    FIsX64 := False;
    Exit;
  end;
  Result := 0; // unknown
end;

function IsUnknown: Boolean;
begin
  Result := (FGameId = 0);
end;

function IsGta3: Boolean;
begin
  Result := (FGameId = 1) or (FGameId = 3);
end;

function IsVc: Boolean;
begin
  Result := (FGameId = 2) or (FGameId = 4);
end;

function IsSA(): Boolean;
begin
  Result := FGameId = 5;
end;

function Is3Master(): Boolean;
begin
  Result := FGameId = 6;
end;

function IsVCMaster(): Boolean;
begin
  Result := FGameId = 7;
end;

function IsSAMaster(): Boolean;
begin
  Result := FGameId = 8;
end;

function IsIV(): Boolean;
begin
  Result := FGameId = 9;
end;

function IsBully(): Boolean;
begin
  Result := FGameId = 10;
end;

function IsRe(): Boolean;
begin
  Result := (FGameId = 1) or (FGameId = 2);
end;


function GetSelfHost: String;
begin
  if EnableSelfHostCb.Checked then
    Result := '1'
  else
    Result := '0';
end;

function OnDownloadProgress(const Url, FileName: String; const Progress, ProgressMax: Int64): Boolean;
begin
  if Progress = ProgressMax then
    Log(Format('Successfully downloaded file to {tmp}: %s', [FileName]));
  Result := True;
end;
            

procedure InitializeWizard;
begin
  DownloadPage := CreateDownloadPage(SetupMessage(msgWizardPreparing), SetupMessage(msgPreparingDesc), @OnDownloadProgress);

  ArchPage := CreateInputOptionPage(wpSelectDir, ExpandConstant('{cm:m2}'), ExpandConstant('{cm:m3}'), ExpandConstant('{cm:m4}'), True, False);
  ReArchPage := CreateInputOptionPage(wpSelectDir, ExpandConstant('{cm:m2}'), ExpandConstant('{cm:m3}'), ExpandConstant('{cm:m8}'), True, False);

  ArchPage.Add(ExpandConstant('{cm:m5}'));
  ArchPage.Add(ExpandConstant('{cm:m6}'));

  ArchPage.Values[0] := True;

  ReArchPage.Add(ExpandConstant('{cm:m5}'));
  ReArchPage.Add(ExpandConstant('{cm:m6}'));
  ReArchPage.Values[0] := True;

  EnableSelfHostCb := TNewCheckBox.Create(ArchPage);
  EnableSelfHostCb.Top := 260;
  EnableSelfHostCb.Width := ArchPage.SurfaceWidth;
  EnableSelfHostCb.Height := ScaleY(17);
  EnableSelfHostCb.Caption := ExpandConstant('{cm:m7}');
  EnableSelfHostCb.Checked := True;
  EnableSelfHostCb.Parent := ArchPage.Surface;
  
end;
   
procedure CurPageChanged(CurPageID: Integer);
var
  I: Integer;
begin
  if CurPageID = wpSelectDir then 
  begin
    // delete \New Folder from the path
    if (DefaultDirOnce) then Exit;
    WizardForm.DirEdit.Text := ExpandConstant('{src}');
    DefaultDirOnce := True;
  end;

   if CurPageID = wpSelectComponents then
   begin
    FGameId := IdentifyGame(WizardDirValue);
     // reset all checkboxes to their initial state first
    for I := 1 to 15 do
    begin
      WizardForm.ComponentsList.ItemEnabled[I] := True;
      WizardForm.ComponentsList.Checked[I] := True;
    end;

    if (IsX64()) then
    begin
      // D3 Wrapper
      WizardForm.ComponentsList.Checked[6] := False;

      // SilentPatch
      WizardForm.ComponentsList.Checked[7] := False;
      WizardForm.ComponentsList.ItemEnabled[7] := False;

      // Frontend Plugin
      WizardForm.ComponentsList.Checked[10] := False;
      WizardForm.ComponentsList.ItemEnabled[10] := False;
    end 
    // 32-bit
    else begin
        if not NeedsD3Wrapper then
        begin
          // D3 Wrapper
          WizardForm.ComponentsList.Checked[6] := False;
          WizardForm.ComponentsList.ItemEnabled[6] := False;
        end;
        if not NeedsSilentPatch then
        begin
          // SilentPatch
          WizardForm.ComponentsList.Checked[7] := False;
          WizardForm.ComponentsList.ItemEnabled[7] := False;
        end;
        if not SupportsFrontend then
        begin
          // Frontend plugin
          WizardForm.ComponentsList.Checked[10] := False;
          WizardForm.ComponentsList.ItemEnabled[10] := False;
        end;
    end;

    // disable IDE Loader for unknown host
    if IsUnknown then
    begin
      // Events Plugin
      WizardForm.ComponentsList.Checked[11] := False;
      WizardForm.ComponentsList.ItemEnabled[11] := False;
      // ide loader
      WizardForm.ComponentsList.Checked[14] := False;
    end;

    // ImGuiRedux is bugged on re3/DE
    if isRe or Is3Master() or IsVCMaster() or IsSAMaster() then
    begin
      // ImGuiRedux
      WizardForm.ComponentsList.Checked[5] := False;

      // D3 Wrapper
      WizardForm.ComponentsList.Checked[6] := False;
      WizardForm.ComponentsList.ItemEnabled[6] := False;
    end;

    // MSS lib is an ASI loader
    if FileExists(ExpandConstant('{app}\Mss32.dll')) then
    begin
       WizardForm.ComponentsList.Checked[15] := False;
    end;
   end;
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
  if (PageID = ArchPage.ID) and not IsUnknown then
    Result := True
  else if (PageID = ReArchPage.ID) and not isRe then
    Result := True
  else
    Result := False;
end;

function NextButtonClick(CurPageID: Integer): Boolean;
var
  FDlAsiLoader: Boolean;
  FDlImGuiPlugin: Boolean;
  FDlMemOpsPlugin: Boolean;
begin
  Result := True;
 
  if (CurPageID = wpSelectDir) and (WizardDirValue <> '') then
  begin
    if ((DirExists(WizardDirValue + '\Gameface\Binaries\Win64')) and (
      FileExists(WizardDirValue + '\PlayGTA3.exe') or 
      FileExists(WizardDirValue + '\PlayGTAViceCity.exe') or 
      FileExists(WizardDirValue + '\PlayGTASanAndreas.exe'))) then
      WizardForm.DirEdit.Text := WizardDirValue + '\Gameface\Binaries\Win64';
    FGameId := IdentifyGame(WizardDirValue);
  end;

  if (CurPageID = wpFinished) then
  begin
    SetIniString('Host', 'EnableSelfHost', GetSelfHost, ExpandConstant('{app}\CLEO\.config\cleo.ini'));
  end;

  if CurPageID = wpReady then 
  begin
    if (FGameId = 0) then
      FGameId := IdentifyGame(WizardDirValue);

    FDlAsiLoader := WizardIsComponentSelected('asiloader');
    FDlImGuiPlugin := WizardIsComponentSelected('plugins/imgui');
    FDlMemOpsPlugin := WizardIsComponentSelected('plugins/memops');

    if FDlAsiLoader or FDlImGuiPlugin or FDlMemOpsPlugin then
    begin
      DownloadPage.Clear;

      if FDlAsiLoader then
      begin
        if IsX64() then
          if isRe then
            DownloadPage.Add('{#UAL64}/d3d9-x64.zip', 'd3d9.zip', '')
          else
            DownloadPage.Add('{#UAL64}/version-x64.zip', 'version.zip', '');
        if IsX86() then
          if IsGta3 or IsVC or IsIV then
            DownloadPage.Add('{#UAL32}/dinput8-Win32.zip', 'dinput8.zip', '')
          else
            DownloadPage.Add('{#UAL32}/vorbisFile-Win32.zip', 'vorbisFile.zip', '');
      end;

      if FDlMemOpsPlugin then
      begin
        if IsX64() then DownloadPage.Add('{#MemOps64}', 'MemoryOperations.zip', '');
        if IsX86() then DownloadPage.Add('{#MemOps32}', 'MemoryOperations.zip', '');
      end;

      if FDlImGuiPlugin then
      begin
        if IsX86() then DownloadPage.Add('{#ImGuiRedux32}/ImGuiReduxWin32.zip', 'ImGuiRedux.zip', '');
        if IsX64() then DownloadPage.Add('{#ImGuiRedux64}/ImGuiReduxWin64.zip', 'ImGuiRedux.zip', '');
        
        if WizardIsComponentSelected('plugins/imgui/d3d8to9') then
          DownloadPage.Add('{#ImGuiRedux32}/d3d8.zip', 'd3d8.zip', '');
        if WizardIsComponentSelected('plugins/imgui/SilentPatch') then
        begin
          if FGameId = 3 then
            DownloadPage.Add('{#SilentPatchIII}', 'SilentPatch.zip', '');
          if FGameId = 4 then
            DownloadPage.Add('{#SilentPatchVC}', 'SilentPatch.zip', '');
          if FGameId = 5 then
            DownloadPage.Add('{#SilentPatchSA}', 'SilentPatch.zip', '');
        end;
          

      end;

      DownloadPage.Show;
      try
        try
          DownloadPage.Download; // This downloads the files to {tmp}
          Result := True;
        except
          if DownloadPage.AbortedByUser then
            Log('Aborted by user.')
          else
            SuppressibleMsgBox(AddPeriod(GetExceptionMessage), mbCriticalError, MB_OK, IDOK);
          Result := False;
        end;
      finally
        DownloadPage.Hide;
      end;
    end;
  end else
    Result := True;
end;



