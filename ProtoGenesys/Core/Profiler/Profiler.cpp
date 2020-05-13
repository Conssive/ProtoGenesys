//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace ProtoGenesys
{
	cProfiler _profiler;

	bool cProfiler::SaveProfile(const std::string& path)
	{
		try
		{
			XML.create_document();
			std::wstring szFilePath;

			if (path.empty())
				szFilePath = acut::AnsiToWstring(acut::GetExeDirectory() + DEFAULT_XML, CP_ACP);

			else
				szFilePath = acut::AnsiToWstring(path, CP_ACP);

			XML.set("ProtoGenesys.AimBot.Mode", gAimBotMode->Current.iValue);
			XML.set("ProtoGenesys.AimBot.AutoZoom", gAutoZoom->Current.bValue);
			XML.set("ProtoGenesys.AimBot.AutoFire", gAutoFire->Current.bValue);
			XML.set("ProtoGenesys.AimBot.AutoWall", gAutoWall->Current.bValue);
			XML.set("ProtoGenesys.AimBot.ApplyPrediction", gApplyPrediction->Current.bValue);
			XML.set("ProtoGenesys.AimBot.AntiTeamKill", gAntiTeamKill->Current.bValue);
			XML.set("ProtoGenesys.AimBot.SilentAim", gSilentAim->Current.bValue);
			XML.set("ProtoGenesys.AimBot.AntiAimPitch", gAntiAimPitch->Current.iValue);
			XML.set("ProtoGenesys.AimBot.AntiAimYaw", gAntiAimYaw->Current.iValue);
			XML.set("ProtoGenesys.AimBot.BoneScan", gBoneScan->Current.iValue);
			XML.set("ProtoGenesys.AimBot.SortMethod", gSortMethod->Current.iValue);

			XML.set("ProtoGenesys.WallHack.Mode", gWallHackMode->Current.iValue);
			XML.set("ProtoGenesys.WallHack.Boxes", gPlayerBoxes->Current.iValue);
			XML.set("ProtoGenesys.WallHack.Bones", gPlayerBones->Current.iValue);
			XML.set("ProtoGenesys.WallHack.SnapLines", gPlayerSnapLines->Current.iValue);
			XML.set("ProtoGenesys.WallHack.Info", gPlayerInfo->Current.bValue);
			XML.set("ProtoGenesys.WallHack.Weapons", gPlayerWeapons->Current.bValue);
			XML.set("ProtoGenesys.WallHack.Entities", gPlayerEntities->Current.bValue);
			XML.set("ProtoGenesys.WallHack.CrossHair", gPlayerCrossHair->Current.bValue);
			XML.set("ProtoGenesys.WallHack.Compass", gPlayerCompass->Current.bValue);
			XML.set("ProtoGenesys.WallHack.Radar", gPlayerRadar->Current.bValue);
			XML.set("ProtoGenesys.WallHack.BulletTracers", gPlayerBulletTracers->Current.bValue);

			XML.set("ProtoGenesys.Miscellaneous.NoFlinch", gNoFlinch->Current.bValue);
			XML.set("ProtoGenesys.Miscellaneous.ThirdPerson", gThirdPerson->Current.bValue);
			XML.set("ProtoGenesys.Miscellaneous.ThirdPersonAntiAim", gThirdPersonAntiAim->Current.bValue);
			XML.set("ProtoGenesys.Miscellaneous.OrbitalVsat", gOrbitalVsat->Current.bValue);
			XML.set("ProtoGenesys.Miscellaneous.HardcoreHud", gHardcoreHud->Current.bValue);
			XML.set("ProtoGenesys.Miscellaneous.DisableEmp", gDisableEmp->Current.bValue);
			XML.set("ProtoGenesys.Miscellaneous.IdStealer", gIdStealer->Current.bValue);
			XML.set("ProtoGenesys.Miscellaneous.AirStuckToggle", gAirStuckToggle->Current.bValue);
			XML.set("ProtoGenesys.Miscellaneous.ReloadCancel", gReloadCancel->Current.bValue);
			XML.set("ProtoGenesys.Miscellaneous.TrickShot", gTrickShot->Current.bValue);

			XML.set("ProtoGenesys.Tweaks.AimBone", gAimBone->Current.iValue);
			XML.set("ProtoGenesys.Tweaks.AimAngle", gAimAngle->Current.iValue);
			XML.set("ProtoGenesys.Tweaks.AimPower", gAimPower->Current.iValue);
			XML.set("ProtoGenesys.Tweaks.AutoAimTime", gAutoAimTime->Current.iValue);
			XML.set("ProtoGenesys.Tweaks.AutoAimDelay", gAutoAimDelay->Current.iValue);
			XML.set("ProtoGenesys.Tweaks.AutoZoomDelay", gAutoZoomDelay->Current.iValue);
			XML.set("ProtoGenesys.Tweaks.AutoFireDelay", gAutoFireDelay->Current.iValue);
			XML.set("ProtoGenesys.Tweaks.RecoilFactor", gRecoilFactor->Current.flValue);
			XML.set("ProtoGenesys.Tweaks.SpreadFactor", gSpreadFactor->Current.flValue);
			XML.set("ProtoGenesys.Tweaks.AntiAimCustomPitch", gAntiAimCustomPitch->Current.flValue);
			XML.set("ProtoGenesys.Tweaks.AntiAimCustomYaw", gAntiAimCustomYaw->Current.flValue);

			XML.set("ProtoGenesys.Colors.Axis.Red", gColorAxis->Current.cValue[0]);
			XML.set("ProtoGenesys.Colors.Axis.Green", gColorAxis->Current.cValue[1]);
			XML.set("ProtoGenesys.Colors.Axis.Blue", gColorAxis->Current.cValue[2]);
			XML.set("ProtoGenesys.Colors.Axis.Alpha", gColorAxis->Current.cValue[3]);

			XML.set("ProtoGenesys.Colors.Allies.Red", gColorAllies->Current.cValue[0]);
			XML.set("ProtoGenesys.Colors.Allies.Green", gColorAllies->Current.cValue[1]);
			XML.set("ProtoGenesys.Colors.Allies.Blue", gColorAllies->Current.cValue[2]);
			XML.set("ProtoGenesys.Colors.Allies.Alpha", gColorAllies->Current.cValue[3]);

			XML.set("ProtoGenesys.Colors.Accents.Red", gColorAccents->Current.cValue[0]);
			XML.set("ProtoGenesys.Colors.Accents.Green", gColorAccents->Current.cValue[1]);
			XML.set("ProtoGenesys.Colors.Accents.Blue", gColorAccents->Current.cValue[2]);
			XML.set("ProtoGenesys.Colors.Accents.Alpha", gColorAccents->Current.cValue[3]);

			XML.set("ProtoGenesys.Colors.CrossHair.Red", gColorCrossHair->Current.cValue[0]);
			XML.set("ProtoGenesys.Colors.CrossHair.Green", gColorCrossHair->Current.cValue[1]);
			XML.set("ProtoGenesys.Colors.CrossHair.Blue", gColorCrossHair->Current.cValue[2]);
			XML.set("ProtoGenesys.Colors.CrossHair.Alpha", gColorCrossHair->Current.cValue[3]);

			XML.set("ProtoGenesys.Colors.Text.Red", gColorText->Current.cValue[0]);
			XML.set("ProtoGenesys.Colors.Text.Green", gColorText->Current.cValue[1]);
			XML.set("ProtoGenesys.Colors.Text.Blue", gColorText->Current.cValue[2]);
			XML.set("ProtoGenesys.Colors.Text.Alpha", gColorText->Current.cValue[3]);

			XML.set("ProtoGenesys.Colors.Shadow.Red", gColorShadow->Current.cValue[0]);
			XML.set("ProtoGenesys.Colors.Shadow.Green", gColorShadow->Current.cValue[1]);
			XML.set("ProtoGenesys.Colors.Shadow.Blue", gColorShadow->Current.cValue[2]);
			XML.set("ProtoGenesys.Colors.Shadow.Alpha", gColorShadow->Current.cValue[3]);

			XML.write_document(szFilePath);

			return true;
		}

		catch (const std::runtime_error & e)
		{
			MessageBox(_mainGui.hWindow, e.what(), "Error", MB_OK | MB_ICONERROR);

			return false;
		}
	}
	/*
	//=====================================================================================
	*/
	bool cProfiler::LoadProfile(const std::string& path)
	{
		try
		{
			std::wstring szFilePath;

			if (path.empty())
				szFilePath = acut::AnsiToWstring(acut::GetExeDirectory() + DEFAULT_XML, CP_ACP);

			else
				szFilePath = acut::AnsiToWstring(path, CP_ACP);

			if (GetFileAttributes(acut::WstringToAnsi(szFilePath, CP_ACP).c_str()) == INVALID_FILE_ATTRIBUTES)
				return false;

			XML.read_from_file(szFilePath);

			XML.get_if_present("ProtoGenesys.AimBot.Mode", gAimBotMode->Current.iValue);
			XML.get_if_present("ProtoGenesys.AimBot.AutoZoom", gAutoZoom->Current.bValue);
			XML.get_if_present("ProtoGenesys.AimBot.AutoFire", gAutoFire->Current.bValue);
			XML.get_if_present("ProtoGenesys.AimBot.AutoWall", gAutoWall->Current.bValue);
			XML.get_if_present("ProtoGenesys.AimBot.ApplyPrediction", gApplyPrediction->Current.bValue);
			XML.get_if_present("ProtoGenesys.AimBot.AntiTeamKill", gAntiTeamKill->Current.bValue);
			XML.get_if_present("ProtoGenesys.AimBot.SilentAim", gSilentAim->Current.bValue);
			XML.get_if_present("ProtoGenesys.AimBot.AntiAimPitch", gAntiAimPitch->Current.iValue);
			XML.get_if_present("ProtoGenesys.AimBot.AntiAimYaw", gAntiAimYaw->Current.iValue);
			XML.get_if_present("ProtoGenesys.AimBot.BoneScan", gBoneScan->Current.iValue);
			XML.get_if_present("ProtoGenesys.AimBot.SortMethod", gSortMethod->Current.iValue);

			XML.get_if_present("ProtoGenesys.WallHack.Mode", gWallHackMode->Current.iValue);
			XML.get_if_present("ProtoGenesys.WallHack.Boxes", gPlayerBoxes->Current.iValue);
			XML.get_if_present("ProtoGenesys.WallHack.Bones", gPlayerBones->Current.iValue);
			XML.get_if_present("ProtoGenesys.WallHack.SnapLines", gPlayerSnapLines->Current.iValue);
			XML.get_if_present("ProtoGenesys.WallHack.Info", gPlayerInfo->Current.bValue);
			XML.get_if_present("ProtoGenesys.WallHack.Weapons", gPlayerWeapons->Current.bValue);
			XML.get_if_present("ProtoGenesys.WallHack.Entities", gPlayerEntities->Current.bValue);
			XML.get_if_present("ProtoGenesys.WallHack.CrossHair", gPlayerCrossHair->Current.bValue);
			XML.get_if_present("ProtoGenesys.WallHack.Compass", gPlayerCompass->Current.bValue);
			XML.get_if_present("ProtoGenesys.WallHack.Radar", gPlayerRadar->Current.bValue);
			XML.get_if_present("ProtoGenesys.WallHack.BulletTracers", gPlayerBulletTracers->Current.bValue);

			XML.get_if_present("ProtoGenesys.Miscellaneous.NoFlinch", gNoFlinch->Current.bValue);
			XML.get_if_present("ProtoGenesys.Miscellaneous.ThirdPerson", gThirdPerson->Current.bValue);
			XML.get_if_present("ProtoGenesys.Miscellaneous.ThirdPersonAntiAim", gThirdPersonAntiAim->Current.bValue);
			XML.get_if_present("ProtoGenesys.Miscellaneous.OrbitalVsat", gOrbitalVsat->Current.bValue);
			XML.get_if_present("ProtoGenesys.Miscellaneous.HardcoreHud", gHardcoreHud->Current.bValue);
			XML.get_if_present("ProtoGenesys.Miscellaneous.DisableEmp", gDisableEmp->Current.bValue);
			XML.get_if_present("ProtoGenesys.Miscellaneous.IdStealer", gIdStealer->Current.bValue);
			XML.get_if_present("ProtoGenesys.Miscellaneous.AirStuckToggle", gAirStuckToggle->Current.bValue);
			XML.get_if_present("ProtoGenesys.Miscellaneous.ReloadCancel", gReloadCancel->Current.bValue);
			XML.get_if_present("ProtoGenesys.Miscellaneous.TrickShot", gTrickShot->Current.bValue);

			XML.get_if_present("ProtoGenesys.Tweaks.AimBone", gAimBone->Current.iValue);
			XML.get_if_present("ProtoGenesys.Tweaks.AimAngle", gAimAngle->Current.iValue);
			XML.get_if_present("ProtoGenesys.Tweaks.AimPower", gAimPower->Current.iValue);
			XML.get_if_present("ProtoGenesys.Tweaks.AutoAimTime", gAutoAimTime->Current.iValue);
			XML.get_if_present("ProtoGenesys.Tweaks.AutoAimDelay", gAutoAimDelay->Current.iValue);
			XML.get_if_present("ProtoGenesys.Tweaks.AutoZoomDelay", gAutoZoomDelay->Current.iValue);
			XML.get_if_present("ProtoGenesys.Tweaks.AutoFireDelay", gAutoFireDelay->Current.iValue);
			XML.get_if_present("ProtoGenesys.Tweaks.RecoilFactor", gRecoilFactor->Current.flValue);
			XML.get_if_present("ProtoGenesys.Tweaks.SpreadFactor", gSpreadFactor->Current.flValue);
			XML.get_if_present("ProtoGenesys.Tweaks.AntiAimCustomPitch", gAntiAimCustomPitch->Current.flValue);
			XML.get_if_present("ProtoGenesys.Tweaks.AntiAimCustomYaw", gAntiAimCustomYaw->Current.flValue);

			XML.get_if_present("ProtoGenesys.Colors.Axis.Red", gColorAxis->Current.cValue[0]);
			XML.get_if_present("ProtoGenesys.Colors.Axis.Green", gColorAxis->Current.cValue[1]);
			XML.get_if_present("ProtoGenesys.Colors.Axis.Blue", gColorAxis->Current.cValue[2]);
			XML.get_if_present("ProtoGenesys.Colors.Axis.Alpha", gColorAxis->Current.cValue[3]);

			XML.get_if_present("ProtoGenesys.Colors.Allies.Red", gColorAllies->Current.cValue[0]);
			XML.get_if_present("ProtoGenesys.Colors.Allies.Green", gColorAllies->Current.cValue[1]);
			XML.get_if_present("ProtoGenesys.Colors.Allies.Blue", gColorAllies->Current.cValue[2]);
			XML.get_if_present("ProtoGenesys.Colors.Allies.Alpha", gColorAllies->Current.cValue[3]);

			XML.get_if_present("ProtoGenesys.Colors.Accents.Red", gColorAccents->Current.cValue[0]);
			XML.get_if_present("ProtoGenesys.Colors.Accents.Green", gColorAccents->Current.cValue[1]);
			XML.get_if_present("ProtoGenesys.Colors.Accents.Blue", gColorAccents->Current.cValue[2]);
			XML.get_if_present("ProtoGenesys.Colors.Accents.Alpha", gColorAccents->Current.cValue[3]);

			XML.get_if_present("ProtoGenesys.Colors.CrossHair.Red", gColorCrossHair->Current.cValue[0]);
			XML.get_if_present("ProtoGenesys.Colors.CrossHair.Green", gColorCrossHair->Current.cValue[1]);
			XML.get_if_present("ProtoGenesys.Colors.CrossHair.Blue", gColorCrossHair->Current.cValue[2]);
			XML.get_if_present("ProtoGenesys.Colors.CrossHair.Alpha", gColorCrossHair->Current.cValue[3]);

			XML.get_if_present("ProtoGenesys.Colors.Text.Red", gColorText->Current.cValue[0]);
			XML.get_if_present("ProtoGenesys.Colors.Text.Green", gColorText->Current.cValue[1]);
			XML.get_if_present("ProtoGenesys.Colors.Text.Blue", gColorText->Current.cValue[2]);
			XML.get_if_present("ProtoGenesys.Colors.Text.Alpha", gColorText->Current.cValue[3]);

			XML.get_if_present("ProtoGenesys.Colors.Shadow.Red", gColorShadow->Current.cValue[0]);
			XML.get_if_present("ProtoGenesys.Colors.Shadow.Green", gColorShadow->Current.cValue[1]);
			XML.get_if_present("ProtoGenesys.Colors.Shadow.Blue", gColorShadow->Current.cValue[2]);
			XML.get_if_present("ProtoGenesys.Colors.Shadow.Alpha", gColorShadow->Current.cValue[3]);

			return true;
		}

		catch (const std::runtime_error & e)
		{
			MessageBox(_mainGui.hWindow, e.what(), "Error", MB_OK | MB_ICONERROR);

			return false;
		}
	}
	/*
	//=====================================================================================
	*/
	void cProfiler::DisableAll()
	{
		gAimBotMode->Current.iValue = gAimBotMode->Reset.iValue;
		gAutoZoom->Current.bValue = gAutoZoom->Reset.bValue;
		gAutoFire->Current.bValue = gAutoFire->Reset.bValue;
		gAutoWall->Current.bValue = gAutoWall->Reset.bValue;
		gApplyPrediction->Current.bValue = gApplyPrediction->Reset.bValue;
		gAntiTeamKill->Current.bValue = gAntiTeamKill->Reset.bValue;
		gSilentAim->Current.bValue = gSilentAim->Reset.bValue;
		gAntiAimPitch->Current.iValue = gAntiAimPitch->Reset.iValue;
		gAntiAimYaw->Current.iValue = gAntiAimYaw->Reset.iValue;
		gBoneScan->Current.iValue = gBoneScan->Reset.iValue;
		gSortMethod->Current.iValue = gSortMethod->Reset.iValue;

		gWallHackMode->Current.iValue = gWallHackMode->Reset.iValue;
		gPlayerBoxes->Current.iValue = gPlayerBoxes->Reset.iValue;
		gPlayerBones->Current.iValue = gPlayerBones->Reset.iValue;
		gPlayerSnapLines->Current.iValue = gPlayerSnapLines->Reset.iValue;
		gPlayerInfo->Current.bValue = gPlayerInfo->Reset.bValue;
		gPlayerWeapons->Current.bValue = gPlayerWeapons->Reset.bValue;
		gPlayerEntities->Current.bValue = gPlayerEntities->Reset.bValue;
		gPlayerCrossHair->Current.bValue = gPlayerCrossHair->Reset.bValue;
		gPlayerCompass->Current.bValue = gPlayerCompass->Reset.bValue;
		gPlayerRadar->Current.bValue = gPlayerRadar->Reset.bValue;
		gPlayerBulletTracers->Current.bValue = gPlayerBulletTracers->Reset.bValue;

		gNoFlinch->Current.bValue = gNoFlinch->Reset.bValue;
		gThirdPerson->Current.bValue = gThirdPerson->Reset.bValue;
		gThirdPersonAntiAim->Current.bValue = gThirdPersonAntiAim->Reset.bValue;
		gOrbitalVsat->Current.bValue = gOrbitalVsat->Reset.bValue;
		gHardcoreHud->Current.bValue = gHardcoreHud->Reset.bValue;
		gDisableEmp->Current.bValue = gDisableEmp->Reset.bValue;
		gIdStealer->Current.bValue = gIdStealer->Reset.bValue;
		gAirStuckToggle->Current.bValue = gAirStuckToggle->Reset.bValue;
		gReloadCancel->Current.bValue = gReloadCancel->Reset.bValue;
		gTrickShot->Current.bValue = gTrickShot->Reset.bValue;
	}
}

//=====================================================================================