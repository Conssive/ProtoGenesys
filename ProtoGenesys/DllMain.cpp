//=====================================================================================

#include "StdAfx.hpp"

using namespace ProtoGenesys;

//=====================================================================================

#define FASTCALL __fastcall
#define USERCALL __cdecl

#define DLLEXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)

#define AttachHook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourAttach((LPVOID*)&original, (LPVOID)hook), DetourTransactionCommit())
#define DetachHook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourDetach((LPVOID*)&original, (LPVOID)hook), DetourTransactionCommit())

//=====================================================================================

void Initialize();
void Deallocate();
void HookFriendApi();
void WINAPI SteamID(LPWSTR xuid);

//=====================================================================================

HRESULT WINAPI hPresent(_In_ IDXGISwapChain* pSwapChain, _In_ UINT SyncInterval, _In_ UINT Flags);
typedef HRESULT(WINAPI* tPresent)(_In_ IDXGISwapChain* pSwapChain, _In_ UINT SyncInterval, _In_ UINT Flags);
tPresent oPresent;

void USERCALL hBulletHitEvent(int localnum, int sourcenum, int targetnum, int weapon, Vector3 start, Vector3 position, Vector3 normal, Vector3 alphanormal, int surface, int _event, int param, int contents, char bone);
typedef void(USERCALL* tBulletHitEvent)(int localnum, int sourcenum, int targetnum, int weapon, Vector3 start, Vector3 position, Vector3 normal, Vector3 alphanormal, int surface, int _event, int param, int contents, char bone);
tBulletHitEvent oBulletHitEvent = (tBulletHitEvent)dwBulletHitEvent;

void USERCALL hTransitionPlayerState(int localnum, sPlayerState* playerstate, LPVOID transplayerstate);
typedef void(USERCALL* tTransitionPlayerState)(int localnum, sPlayerState* playerstate, LPVOID transplayerstate);
tTransitionPlayerState oTransitionPlayerState = (tTransitionPlayerState)dwTransitionPlayerState;

void USERCALL hCalcEntityLerpPositions(int localnum, sCEntity* entity);
typedef void(USERCALL* tCalcEntityLerpPositions)(int localnum, sCEntity* entity);
tCalcEntityLerpPositions oCalcEntityLerpPositions = (tCalcEntityLerpPositions)dwCalcEntityLerpPositions;

int USERCALL hGetWorldTagMatrix(LPVOID pose, LPVOID dobj, WORD tag, Vector3 matrix[], Vector3 origin);
typedef int(USERCALL* tGetWorldTagMatrix)(LPVOID pose, LPVOID dobj, WORD tag, Vector3 matrix[], Vector3 origin);
tGetWorldTagMatrix oGetWorldTagMatrix = (tGetWorldTagMatrix)dwGetWorldTagMatrix;

LPVOID USERCALL hGetAddr(bool renew);
typedef LPVOID(USERCALL* tGetAddr)(bool renew);
tGetAddr oGetAddr = (tGetAddr)dwGetAddr;

int USERCALL hGameTypeSettings(int setting);
typedef int(USERCALL* tGameTypeSettings)(int setting);
tGameTypeSettings oGameTypeSettings = (tGameTypeSettings)dwGameTypeSettings;

int USERCALL hGetPlayerStatus(int localnum, DWORD xuid1, DWORD xuid2);
typedef int(USERCALL* tGetPlayerStatus)(int localnum, DWORD xuid1, DWORD xuid2);
tGetPlayerStatus oGetPlayerStatus = (tGetPlayerStatus)dwGetPlayerStatus;

bool FASTCALL hSteamIDIsValid(CSteamID* steamid);
typedef bool(FASTCALL* tSteamIDIsValid)(CSteamID* steamid);
tSteamIDIsValid oSteamIDIsValid = (tSteamIDIsValid)dwSteamIDIsValid;

LPCSTR FASTCALL hGetPersonaName(LPVOID ecx, LPVOID edx);
typedef LPCSTR(FASTCALL* tGetPersonaName)(LPVOID ecx, LPVOID edx);
tGetPersonaName oGetPersonaName;

CSteamID* FASTCALL hGetSteamID(LPVOID ecx, LPVOID edx, int unk);
typedef CSteamID*(FASTCALL* tGetSteamID)(LPVOID ecx, LPVOID edx, int unk);
tGetSteamID oGetSteamID;

int FASTCALL hGetFriendCount(LPVOID ecx, LPVOID edx, EFriendFlags friendflags);
typedef int(FASTCALL* tGetFriendCount)(LPVOID ecx, LPVOID edx, EFriendFlags friendflags);
tGetFriendCount oGetFriendCount;

void FASTCALL hGetFriendByIndex(LPVOID ecx, LPVOID edx, CSteamID* steamid, int index, EFriendFlags friendflags);
typedef void(FASTCALL* tGetFriendByIndex)(LPVOID ecx, LPVOID edx, CSteamID* steamid, int index, EFriendFlags friendflags);
tGetFriendByIndex oGetFriendByIndex;

EPersonaState FASTCALL hGetFriendPersonaState(LPVOID ecx, LPVOID edx, CSteamID steamid);
typedef EPersonaState(FASTCALL* tGetFriendPersonaState)(LPVOID ecx, LPVOID edx, CSteamID steamid);
tGetFriendPersonaState oGetFriendPersonaState;

LPCSTR FASTCALL hGetFriendPersonaName(LPVOID ecx, LPVOID edx, CSteamID steamid);
typedef LPCSTR(FASTCALL* tGetFriendPersonaName)(LPVOID ecx, LPVOID edx, CSteamID steamid);
tGetFriendPersonaName oGetFriendPersonaName;

bool FASTCALL hGetFriendGamePlayed(CSteamID steamid, int unk1, int unk2, FriendGameInfo_t* friendgameinfo);
typedef bool(FASTCALL* tGetFriendGamePlayed)(CSteamID steamid, int unk1, int unk2, FriendGameInfo_t* friendgameinfo);
tGetFriendGamePlayed oGetFriendGamePlayed;

int USERCALL hAtoi1(LPCSTR string);
int USERCALL hAtoi2(LPCSTR string);

//=====================================================================================

FurtiveHook fhTransitionPlayerStateCall{ x86Instruction::CALL, (LPVOID)dwTransitionPlayerStateCall, &hTransitionPlayerState };
FurtiveHook fhGetWorldTagMatrixCall{ x86Instruction::CALL, (LPVOID)dwGetWorldTagMatrixCall, &hGetWorldTagMatrix };
FurtiveHook fhGameTypeSettingsCall{ x86Instruction::CALL, (LPVOID)dwGameTypeSettingsCall, &hGameTypeSettings };

FurtiveHook fhAtoiCall1{ x86Instruction::CALL, (LPVOID)dwAtoiCall1, &hAtoi1 };
FurtiveHook fhAtoiCall2{ x86Instruction::CALL, (LPVOID)dwAtoiCall2, &hAtoi2 };

//=====================================================================================

HRESULT WINAPI hPresent(_In_ IDXGISwapChain* swapchain, _In_ UINT syncinterval, _In_ UINT flags)
{
	_mainGui.Present(swapchain, syncinterval, flags);

	return oPresent(swapchain, syncinterval, flags);
}

//=====================================================================================

void USERCALL hBulletHitEvent(int localnum, int sourcenum, int targetnum, int weapon, Vector3 start, Vector3 position, Vector3 normal, Vector3 alphanormal, int surface, int _event, int param, int contents, char bone)
{
	oBulletHitEvent(localnum, sourcenum, targetnum, weapon, start, position, normal, alphanormal, surface, _event, param, contents, bone);

	_hooks.BulletHitEvent(localnum, sourcenum, targetnum, weapon, start, position, normal, alphanormal, surface, _event, param, contents, bone);
}

//=====================================================================================

void USERCALL hTransitionPlayerState(int localnum, sPlayerState* playerstate, LPVOID transplayerstate)
{
	_hooks.TransitionPlayerState(localnum, playerstate, transplayerstate);

	oTransitionPlayerState(localnum, playerstate, transplayerstate);
}

//=====================================================================================

void USERCALL hCalcEntityLerpPositions(int localnum, sCEntity* entity)
{
	oCalcEntityLerpPositions(localnum, entity);

	return _hooks.CalcEntityLerpPositions(localnum, entity);
}

//=====================================================================================

int USERCALL hGetWorldTagMatrix(LPVOID pose, LPVOID dobj, WORD tag, Vector3 matrix[], Vector3 origin)
{
	int iReturn = oGetWorldTagMatrix(pose, dobj, tag, matrix, origin);

	_hooks.GetWorldTagMatrix(pose, dobj, tag, matrix, origin);

	return iReturn;
}

//=====================================================================================

LPVOID USERCALL hGetAddr(bool renew)
{
	_hooks.GetAddr(renew);

	return oGetAddr(renew);
}

//=====================================================================================

int USERCALL hGameTypeSettings(int setting)
{
	return _hooks.GameTypeSettings(setting);
}

//=====================================================================================

int USERCALL hGetPlayerStatus(int localnum, DWORD xuid1, DWORD xuid2)
{
	return _hooks.GetPlayerStatus(localnum, xuid1, xuid2);
}

//=====================================================================================

bool FASTCALL hSteamIDIsValid(CSteamID* steamid)
{
	return _hooks.SteamIDIsValid(steamid);
}

//=====================================================================================

CSteamID* FASTCALL hGetSteamID(LPVOID ecx, LPVOID edx, int unk)
{
	return _hooks.GetSteamID(oGetSteamID(ecx, edx, unk));
}

//=====================================================================================

LPCSTR FASTCALL hGetPersonaName(LPVOID ecx, LPVOID edx)
{
	return _hooks.GetPersonaName(oGetPersonaName(ecx, edx));
}

//=====================================================================================

int FASTCALL hGetFriendCount(LPVOID ecx, LPVOID edx, EFriendFlags friendflags)
{
	_hooks.iFriendCount = oGetFriendCount(ecx, edx, friendflags);

	return _hooks.GetFriendCount(ecx, edx, friendflags) + _hooks.iFriendCount;
}

//=====================================================================================

void FASTCALL hGetFriendByIndex(LPVOID ecx, LPVOID edx, CSteamID* steamid, int index, EFriendFlags friendflags)
{
	if (index >= 0 && index < _hooks.iFriendCount)
		oGetFriendByIndex(ecx, edx, steamid, index, friendflags);

	if (index >= _hooks.iFriendCount && index < _hooks.iFriendCount + (int)_hooks.vFriends.size())
		_hooks.GetFriendByIndex(ecx, edx, steamid, index, friendflags);
}

//=====================================================================================

EPersonaState FASTCALL hGetFriendPersonaState(LPVOID ecx, LPVOID edx, CSteamID steamid)
{
	return _hooks.GetFriendPersonaState(ecx, edx, steamid);
}

//=====================================================================================

LPCSTR FASTCALL hGetFriendPersonaName(LPVOID ecx, LPVOID edx, CSteamID steamid)
{
	LPCSTR szName = _hooks.GetFriendPersonaName(ecx, edx, steamid);

	if (szName)
		return szName;

	return oGetFriendPersonaName(ecx, edx, steamid);
}

//=====================================================================================

bool FASTCALL hGetFriendGamePlayed(CSteamID steamid, int unk1, int unk2, FriendGameInfo_t* friendgameinfo)
{
	return _hooks.GetFriendGamePlayed(steamid, unk1, unk2, friendgameinfo);
}

//=====================================================================================

int USERCALL hAtoi1(LPCSTR string)
{
	return _hooks.Atoi1(atoi(string));
}

//=====================================================================================

int USERCALL hAtoi2(LPCSTR string)
{
	return _hooks.Atoi2(atoi(string));
}

//=====================================================================================

void Initialize(HINSTANCE hinstDLL)
{
	_mainGui.hInstDll = hinstDLL;
	_hooks.PatchAntiCheat();

	_hooks.pUnhandledExceptionFilter = SetUnhandledExceptionFilter(NULL);
	_hooks.pVectoredExceptionHandler = AddVectoredExceptionHandler(TRUE, _hooks._thunkVectoredExceptionHandler.GetThunk());

	_hooks.dwConnectPaths = *(DWORD_PTR*)dwConnectPathsDvar;
	*(DWORD_PTR*)dwConnectPathsDvar = cHooks::VEH_INDEX_CONNECTPATHS;

	_hooks.dwMouseAccel = *(DWORD_PTR*)dwMouseAccelerationDvar;
	*(DWORD_PTR*)dwMouseAccelerationDvar = cHooks::VEH_INDEX_MOUSEACCEL;

	_hooks.dwDrawBigFPS = *(DWORD_PTR*)dwDrawBigFPSDvar;
	*(DWORD_PTR*)dwDrawBigFPSDvar = cHooks::VEH_INDEX_DRAWBIGFPS;

	_hooks.dwMaxClients = *(DWORD_PTR*)dwMaxClientsDvar;
	*(DWORD_PTR*)dwMaxClientsDvar = cHooks::VEH_INDEX_MAXCLIENTS;

	_hooks.dwNoDelta = *(DWORD_PTR*)dwNoDeltaDvar;
	*(DWORD_PTR*)dwNoDeltaDvar = cHooks::VEH_INDEX_NODELTA;

	oPresent = (tPresent)SwapVMT((bIsSteamVersion && bGameOverlayRenderer) ? (DWORD_PTR)&dwPresent : dwPresent, (DWORD_PTR)&hPresent, (bIsSteamVersion && bGameOverlayRenderer) ? 0 : 8);

	AttachHook(oBulletHitEvent, hBulletHitEvent);
	AttachHook(oCalcEntityLerpPositions, hCalcEntityLerpPositions);
	AttachHook(oGetAddr, hGetAddr);
	AttachHook(oGetPlayerStatus, hGetPlayerStatus);
	AttachHook(oSteamIDIsValid, hSteamIDIsValid);

	fhTransitionPlayerStateCall.SetHook();
	fhGetWorldTagMatrixCall.SetHook();
	fhGameTypeSettingsCall.SetHook();

	fhAtoiCall1.SetHook();
	fhAtoiCall2.SetHook();

	HookFriendApi();
}

//=====================================================================================

void Deallocate()
{
	*(DWORD_PTR*)dwConnectPathsDvar = _hooks.dwConnectPaths;
	*(DWORD_PTR*)dwMouseAccelerationDvar = _hooks.dwMouseAccel;
	*(DWORD_PTR*)dwDrawBigFPSDvar = _hooks.dwDrawBigFPS;
	*(DWORD_PTR*)dwMaxClientsDvar = _hooks.dwMaxClients;
	*(DWORD_PTR*)dwNoDeltaDvar = _hooks.dwNoDelta;

	RemoveVectoredExceptionHandler(_hooks.pVectoredExceptionHandler);
	SetUnhandledExceptionFilter(_hooks.pUnhandledExceptionFilter);

	SwapVMT((bIsSteamVersion && bGameOverlayRenderer) ? (DWORD_PTR)&dwPresent : dwPresent, (DWORD_PTR)oPresent, (bIsSteamVersion && bGameOverlayRenderer) ? 0 : 8);

	DetachHook(oBulletHitEvent, hBulletHitEvent);
	DetachHook(oCalcEntityLerpPositions, hCalcEntityLerpPositions);
	DetachHook(oGetAddr, hGetAddr);
	DetachHook(oGetPlayerStatus, hGetPlayerStatus);
	DetachHook(oSteamIDIsValid, hSteamIDIsValid);

	fhTransitionPlayerStateCall.UnHook();
	fhGetWorldTagMatrixCall.UnHook();
	fhGameTypeSettingsCall.UnHook();

	fhAtoiCall1.UnHook();
	fhAtoiCall2.UnHook();

	if (oGetSteamID)
		SwapVMT((DWORD_PTR)_hooks._steamUser, (DWORD_PTR)oGetSteamID, 2);

	if (oGetPersonaName)
		SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)oGetPersonaName, 0);

	if (oGetFriendCount)
		SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)oGetFriendCount, 3);

	if (oGetFriendByIndex)
		SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)oGetFriendByIndex, 4);

	if (oGetFriendPersonaState)
		SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)oGetFriendPersonaState, 6);

	if (oGetFriendPersonaName)
		SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)oGetFriendPersonaName, 7);

	if (oGetFriendGamePlayed)
		SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)oGetFriendGamePlayed, 8);

	_mainGui.pDevice->Release();
	_mainGui.pDeviceContext->Release();

	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtr(_mainGui.hWindow, GWLP_WNDPROC, (LONG_PTR)_mainGui.oWindowProcess);
}

//=====================================================================================

void HookFriendApi()
{
	_hooks.RefreshFriends();

	if (!hSteamAPI)
		return;

	_hooks.dwSteamFriends = (DWORD_PTR)GetProcAddress(hSteamAPI, "SteamFriends");

	if (!_hooks.dwSteamFriends)
		return;

	_hooks._steamFriends = VariadicCall<ISteamFriends*>(_hooks.dwSteamFriends);

	if (!_hooks._steamFriends)
		return;

	oGetPersonaName = (tGetPersonaName)SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)&hGetPersonaName, 0);
	oGetFriendCount = (tGetFriendCount)SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)&hGetFriendCount, 3);
	oGetFriendByIndex = (tGetFriendByIndex)SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)&hGetFriendByIndex, 4);
	oGetFriendPersonaState = (tGetFriendPersonaState)SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)&hGetFriendPersonaState, 6);
	oGetFriendPersonaName = (tGetFriendPersonaName)SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)&hGetFriendPersonaName, 7);
	oGetFriendGamePlayed = (tGetFriendGamePlayed)SwapVMT((DWORD_PTR)_hooks._steamFriends, (DWORD_PTR)&hGetFriendGamePlayed, 8);
}

//=====================================================================================

void WINAPI SteamID(LPWSTR xuid)
{
#pragma DLLEXPORT

	_hooks.qwXuidOverride = wcstoll(xuid, NULL, 10);

	if (!hSteamAPI)
		return;

	_hooks.dwSteamUser = (DWORD_PTR)GetProcAddress(hSteamAPI, "SteamUser");

	if (!_hooks.dwSteamUser)
		return;

	_hooks._steamUser = VariadicCall<ISteamUser*>(_hooks.dwSteamUser);

	if (!_hooks._steamUser)
		return;

	oGetSteamID = (tGetSteamID)SwapVMT((DWORD_PTR)_hooks._steamUser, (DWORD_PTR)&hGetSteamID, 2);
}

//=====================================================================================

BOOL APIENTRY DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	DisableThreadLibraryCalls(hinstDLL);

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		Initialize(hinstDLL);
		return TRUE;

	case DLL_PROCESS_DETACH:
		Deallocate();
		return TRUE;

	default:
		return FALSE;
	}
}

//=====================================================================================