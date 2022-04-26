#define AppName "CLEO Redux"
#define AppVersion "0.9.4-dev.20220426"
#define AppPublisher "Seemann"
#define AppURL "https://re.cleo.li"
#define SourceDir "..\..\cleo_redux_plugins_release"
#define UAL64Repo = "https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/x64-latest"
#define UAL32Repo = "https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/Win32-latest"

#define ImGuiReduxRepo = "https://github.com/user-grinch/ImGuiRedux/releases/download/x86-latest"
#define SilentPatchIII = "https://silent.rockstarvision.com/uploads/SilentPatchIII.zip"
#define SilentPatchVC = "https://silent.rockstarvision.com/uploads/SilentPatchVC.zip"
#define SilentPatchSA = "https://silent.rockstarvision.com/uploads/SilentPatchSA.zip"

[Setup]
AppId={{511AFCDA-FD5E-491C-A1B7-22BAC8F93711}
AppName={#AppName}
AppVersion={#AppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#AppPublisher}
AppPublisherURL={#AppURL}
AppCopyright=Copyright (c) 2021-2022, {#AppPublisher}
DefaultDirName=New folder
LicenseFile={#SourceDir}\Release\LICENSE.txt
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
;PrivilegesRequiredOverridesAllowed=dialog
OutputDir=build
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
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"; LicenseFile: "LICENSE-RU.txt"

[Types]
Name: "full"; Description: "Full"; Flags: iscustom

[Components]
Name: "program"; Description: "CLEO Redux"; Types: full; Flags: fixed
Name: "plugins"; Description: "Plugins"; Types: full
Name: "plugins/ini"; Description: "IniFiles 1.2"; Types: full
Name: "plugins/dylib"; Description: "Dylib 1.1"; Types: full
Name: "plugins/imgui"; Description: "ImGuiRedux (by Grinch_) - x86 only"; Types: full
Name: "plugins/imgui/d3d8to9"; Description: "d3d8to9 Wrapper - for GTA III and GTA Vice City"; Types: full
Name: "plugins/imgui/SilentPatch"; Description: "SilentPatch - needed for the mouse to work properly"; Types: full
Name: "asiloader"; Description: "Ultimate ASI Loader (by ThirteenAG)"; Types: full

[Dirs]
Name: "{app}"; Permissions: users-modify
Name: "{app}\CLEO"; Permissions: users-modify

[Files]
; CLEO
Source: "{#SourceDir}\cleo_redux.asi"; DestDir: "{app}"; Flags: ignoreversion; Check: IsX86;  Components: program;
Source: "{#SourceDir}\cleo_redux64.asi"; DestDir: "{app}"; Flags: ignoreversion; Check: IsX64;  Components: program;
; Source: "{#SourceDir}\Release\LICENSE.txt"; DestDir: "{app}"; DestName: "CLEO_REDUX_LICENSE.txt"; Flags: ignoreversion;  Components: program

; UAL
Source: "{tmp}\version.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: NeedsAL and IsX64; AfterInstall: Extract('{app}\version.zip', 'version.dll', '{app}');  Components: asiloader;
Source: "{tmp}\vorbisFile.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: NeedsAL and IsX86; AfterInstall: Extract('{app}\vorbisFile.zip', 'vorbisFile.dll', '{app}');  Components: asiloader;

; Plugins
Source: "{#SourceDir}\Release\CLEO\CLEO_PLUGINS\dylib.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: plugins/dylib
Source: "{#SourceDir}\Release\CLEO\CLEO_PLUGINS\dylib64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: plugins/dylib
Source: "{#SourceDir}\Release\CLEO\CLEO_PLUGINS\IniFiles.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: plugins/ini
Source: "{#SourceDir}\Release\CLEO\CLEO_PLUGINS\IniFiles64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: plugins/ini
Source: "{tmp}\ImGuiRedux.zip"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: deleteafterinstall external; Check: IsX86; AfterInstall: Extract('{app}\CLEO\CLEO_PLUGINS\ImGuiRedux.zip', 'ImGuiRedux.cleo', '{app}\CLEO\CLEO_PLUGINS'); Components: plugins/imgui;
Source: "{tmp}\d3d8.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: IsX86 and NeedsD3Wrapper; AfterInstall: Extract('{app}\d3d8.zip', 'd3d8.dll', '{app}'); Components: plugins/imgui/d3d8to9;
Source: "{tmp}\SilentPatch.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; Check: IsX86 and NeedsSilentPatch; AfterInstall: ExtractAll('{app}\SilentPatch.zip', '{app}'); Components: plugins/imgui/SilentPatch;


[CustomMessages]
m2 =Select CLEO Redux version
m3 =Which version of CLEO Redux (32-bit or 64-bit) should be installed?
m4 =No supported game or application was found in the selected directory. To continue installation select either one of the two available versions of CLEO Redux. Hint: it should match the version (architecture) of the target game or application that will run CLEO Redux.
m5 =32-bit (x86)
m6 =64-bit (x64)

russian.m2 =Выберите версию CLEO Redux
russian.m3 =Какую версию CLEO Redux (32-битную или 64-битную) нужно установить?
russian.m4 =В выбранной директории не нашлось поддерживаемых игр или приложений. Для продолжения установки, выберите одну из двух возможных версий CLEO Redux. Подсказка: она должна совпадать с версией (архитектурой) игры или приложения, в которой будет запускаться CLEO Redux.
russian.m5 =32-битная (x86)
russian.m6 =64-битная (x64)
           
[Code]
const
  SHCONTCH_NOPROGRESSBOX = 4;
  SHCONTCH_RESPONDYESTOALL = 16;

var
  FIsX64: Boolean;
  FNeedsAL: Boolean;
  FGameId: Integer;
  DownloadPage: TDownloadWizardPage;
  ArchPage: TInputOptionWizardPage;
  AssociateCheckBox: TCheckBox;
  AssociateLabel: TLabel;
  DefaultDirOnce: Boolean;

function IsX64(): Boolean;
begin
  Result := FIsX64 or ArchPage.Values[1];
end;

function IsX86(): Boolean;
begin
  Result := not IsX64();
end;

function NeedsAL(): Boolean;
begin
  Result := FNeedsAL;
end;

function NeedsD3Wrapper(): Boolean;
begin
  Result := (FGameId >= 0) and (FGameId < 5);
end;

function NeedsSilentPatch(): Boolean;
begin
  Result := (FGameId in [3, 4, 5]);
end;

function IsSA(): Boolean;
begin
  Result := FGameId = 5;
end;

procedure unzipFile(Src, FileName, TargetFldr: PAnsiChar);
var
  Shell: variant;
  Item: variant;
  SrcFldr, DestFldr: variant;
  shellfldritems: variant;
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
  Item: variant;
  SrcFldr, DestFldr: variant;
  shellfldritems: variant;
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

function IdentifyGame(Dir: String): Integer;
begin
  if FileExists(Dir + '\re3.exe') then
  begin
    Result := 1;
    FIsX64 := False;
    FNeedsAL := False;
    Exit;
  end;
  if FileExists(Dir + '\revc.exe') then
  begin
    Result := 2;
    FIsX64 := False;
    FNeedsAL := False;
    Exit;
  end;
  if FileExists(Dir + '\gta3.exe') then
  begin
    Result := 3;
    FIsX64 := False;
    FNeedsAL := False;
    Exit;
  end;
  if FileExists(Dir + '\gta-vc.exe') then
  begin
    Result := 4;
    FIsX64 := False;
    FNeedsAL := False;
    Exit;
  end;
  if FileExists(Dir + '\gta_sa.exe') or FileExists(Dir + '\gta-sa.exe') or FileExists(Dir + '\gta_sa_compact.exe') then
  begin
    Result := 5;
    FIsX64 := False;
    FNeedsAL := True;
    Exit;
  end;
  if FileExists(Dir + '\libertycity.exe') then
  begin
    Result := 6;
    FIsX64 := True;
    FNeedsAL := True;
    Exit;
  end;
  if FileExists(Dir + '\vicecity.exe') then
  begin
    Result := 7;
    FIsX64 := True;
    FNeedsAL := True;
    Exit;
  end;
  if FileExists(Dir + '\sanandreas.exe') then
  begin
    Result := 8;
    FIsX64 := True;
    FNeedsAL := True;
    Exit;
  end;
  FNeedsAL := True; // unknown
  Result := 0; // unknown
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

  ArchPage.Add(ExpandConstant('{cm:m5}'));
  ArchPage.Add(ExpandConstant('{cm:m6}'));

  ArchPage.Values[0] := True;
  
end;
   
procedure CurPageChanged(CurPageID: Integer);
begin
  if CurPageID = wpSelectDir then 
  begin
    // delete \New Folder from the path
    if (DefaultDirOnce) then Exit;
    WizardForm.DirEdit.Text := ExpandConstant('{src}');
    DefaultDirOnce := True;
  end;

   if CurPageID = wpSelectComponents then
    if (IsX64()) then
    begin
      WizardForm.ComponentsList.Checked[4] := False;
      WizardForm.ComponentsList.ItemEnabled[4] := False;
      WizardForm.ComponentsList.Checked[5] := False;
      WizardForm.ComponentsList.ItemEnabled[5] := False;
      WizardForm.ComponentsList.Checked[6] := False;
      WizardForm.ComponentsList.ItemEnabled[6] := False;
    end else begin
        if not NeedsD3Wrapper then
        begin
          WizardForm.ComponentsList.Checked[5] := False;
          WizardForm.ComponentsList.ItemEnabled[5] := False;
        end;
    end;
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
  if (PageID = ArchPage.ID) and (FGameId > 0) then
    Result := True
  else
    Result := False;
end;

function NextButtonClick(CurPageID: Integer): Boolean;
var
  FDlAsiLoader: Boolean;
  FDlImGuiPlugin: Boolean;
begin
  Result := True;
 
  if (CurPageID = wpSelectDir) and (WizardDirValue <> '') then
  begin
    FGameId := IdentifyGame(WizardDirValue);   
  end;

  if CurPageID = wpReady then 
  begin
    if (FGameId = 0) then
      FGameId := IdentifyGame(WizardDirValue);

    FDlAsiLoader := (WizardIsComponentSelected('asiloader') and (FGameId in [0, 5, 6, 7, 8]));
    FDlImGuiPlugin := WizardIsComponentSelected('plugins/imgui');

    if FDlAsiLoader or FDlImGuiPlugin then
    begin
      DownloadPage.Clear;

      if FDlAsiLoader then
      begin
        if IsX64() then DownloadPage.Add('{#UAL64Repo}/version.zip', 'version.zip', '');
        if IsX86() then DownloadPage.Add('{#UAL32Repo}/vorbisFile.zip', 'vorbisFile.zip', '');
      end;

      if FDlImGuiPlugin then
      begin
        DownloadPage.Add('{#ImGuiReduxRepo}/ImGuiRedux.zip', 'ImGuiRedux.zip', '');
        if WizardIsComponentSelected('plugins/imgui/d3d8to9') then
          DownloadPage.Add('{#ImGuiReduxRepo}/d3d8.zip', 'd3d8.zip', '');
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



