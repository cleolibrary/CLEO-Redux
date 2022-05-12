#define AppName "CLEO Redux"
#define AppVersion "0.9.4"
#define AppPublisher "Seemann"
#define AppURL "https://re.cleo.li"
#define SourceDir "..\"

#define UAL64 = "https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/x64-latest"
#define UAL32 = "https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/Win32-latest"

#define ImGuiRedux32 = "https://github.com/user-grinch/ImGuiRedux/releases/download/Win32-latest"
#define ImGuiRedux64 = "https://github.com/user-grinch/ImGuiRedux/releases/download/Win64-latest"

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
LicenseFile={#SourceDir}\LICENSE.txt
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
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"; LicenseFile: "..\LICENSE-RU.txt"

[Types]
Name: "full"; Description: "Full"; Flags: iscustom

[Components]
Name: "program"; Description: "CLEO Redux"; Types: full; Flags: fixed
Name: "plugins"; Description: "New Commands"; Types: full
Name: "plugins/ini"; Description: "IniFiles 1.2"; Types: full
Name: "plugins/dylib"; Description: "Dylib 1.1"; Types: full
Name: "plugins/imgui"; Description: "ImGuiRedux (by Grinch_)"; Types: full
Name: "plugins/imgui/d3d8to9"; Description: "d3d8to9 Wrapper - for games using DirectX 8"; Types: full
Name: "plugins/imgui/SilentPatch"; Description: "SilentPatch - needed for the mouse to work properly in classic GTA"; Types: full
Name: "loaders"; Description: "File Loaders"; Types: full
Name: "loaders/text"; Description: "*.txt files"; Types: full
Name: "loaders/ide"; Description: "*.ide files (for 32-bit GTA3, VC, SA)"; Types: full

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
Source: "{#SourceDir}\plugins\Dylib\build\dylib.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: plugins/dylib
Source: "{#SourceDir}\plugins\Dylib\build\dylib64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: plugins/dylib
Source: "{#SourceDir}\plugins\IniFiles\build\IniFiles.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: plugins/ini
Source: "{#SourceDir}\plugins\IniFiles\build\IniFiles64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: plugins/ini

Source: "{tmp}\ImGuiRedux.zip"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: deleteafterinstall external; Check: IsX86; AfterInstall: InstallImGuiRedux32; Components: plugins/imgui;
Source: "{tmp}\ImGuiRedux.zip"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: deleteafterinstall external; Check: IsX64; AfterInstall: Extract('{app}\CLEO\CLEO_PLUGINS\ImGuiRedux.zip', 'ImGuiReduxWin64.cleo', '{app}\CLEO\CLEO_PLUGINS'); Components: plugins/imgui;

Source: "{tmp}\d3d8.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; AfterInstall: Extract('{app}\d3d8.zip', 'd3d8.dll', '{app}'); Components: plugins/imgui/d3d8to9;
Source: "{tmp}\SilentPatch.zip"; DestDir: "{app}"; Flags: deleteafterinstall external; AfterInstall: ExtractAll('{app}\SilentPatch.zip', '{app}'); Components: plugins/imgui/SilentPatch;

; Custom File Loaders
Source: "{#SourceDir}\loaders\TextLoader\build\TextLoader.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: loaders/text
Source: "{#SourceDir}\loaders\TextLoader\build\TextLoader64.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX64; Components: loaders/text
Source: "{#SourceDir}\loaders\IdeLoader\build\IdeLoader.cleo"; DestDir: "{app}\CLEO\CLEO_PLUGINS"; Flags: ignoreversion; Check: IsX86; Components: loaders/ide


[CustomMessages]
m2 =Select CLEO Redux version
m3 =Which version of CLEO Redux (32-bit or 64-bit) should be installed?
m4 =No supported game or application was found in the selected directory. To continue installation select either one of the two available versions of CLEO Redux. Hint: it should match the version (architecture) of the target game or application that will run CLEO Redux.
m5 =32-bit (x86)
m6 =64-bit (x64)

russian.m2 =�������� ������ CLEO Redux
russian.m3 =����� ������ CLEO Redux (32-������ ��� 64-������) ����� ����������?
russian.m4 =� ��������� ���������� �� ������� �������������� ��� ��� ����������. ��� ����������� ���������, �������� ���� �� ���� ��������� ������ CLEO Redux. ���������: ��� ������ ��������� � ������� (������������) ���� ��� ����������, � ������� ����� ����������� CLEO Redux.
russian.m5 =32-������ (x86)
russian.m6 =64-������ (x64)
           
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
     // reset all checkboxes to their initial state first
    for I := 1 to 9 do
    begin
      WizardForm.ComponentsList.ItemEnabled[I] := True;
      WizardForm.ComponentsList.Checked[I] := True;
    end;

    if (IsX64()) then
    begin
      // D3 Wrapper
      WizardForm.ComponentsList.Checked[5] := False;

      // SilentPatch
      WizardForm.ComponentsList.Checked[6] := False;
      WizardForm.ComponentsList.ItemEnabled[6] := False;

      // ide loader
      WizardForm.ComponentsList.Checked[9] := False;
      WizardForm.ComponentsList.ItemEnabled[9] := False;
    end 
    // 32-bit
    else begin
        if not NeedsD3Wrapper then
        begin
          WizardForm.ComponentsList.Checked[5] := False;
          WizardForm.ComponentsList.ItemEnabled[5] := False;
        end;
        if not NeedsSilentPatch then
        begin
          WizardForm.ComponentsList.Checked[6] := False;
          WizardForm.ComponentsList.ItemEnabled[6] := False;
        end;
    end;

    // disable IDE Loader for unknown host
    if (FGameId = 0) then
    begin
      // ide loader
      WizardForm.ComponentsList.Checked[9] := False;
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
        if IsX64() then DownloadPage.Add('{#UAL64}/version.zip', 'version.zip', '');
        if IsX86() then DownloadPage.Add('{#UAL32}/vorbisFile.zip', 'vorbisFile.zip', '');
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



