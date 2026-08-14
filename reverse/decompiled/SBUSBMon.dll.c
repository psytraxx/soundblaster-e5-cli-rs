/* === FUN_00408208 @ 00408208 === */

void FUN_00408208(void)

{
  return;
}



/* === FUN_00408220 @ 00408220 === */

undefined8 * FUN_00408220(undefined8 *param_1,uint param_2)

{
  *param_1 = &PTR_FUN_00401728;
  if ((HANDLE)param_1[2] != (HANDLE)0x0) {
    CloseHandle((HANDLE)param_1[2]);
    param_1[2] = 0;
  }
  if ((param_2 & 1) != 0) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_00408270 @ 00408270 === */

undefined8 FUN_00408270(void)

{
  return 1;
}



/* === SBAVMonitor @ 0040827c === */

undefined8 SBAVMonitor(void)

{
  HRESULT HVar1;
  BOOL BVar2;
  undefined8 uVar3;
  tagMSG local_38;
  
                    /* 0x827c  1  SBAVMonitor */
  FUN_00408208();
  if (((DAT_00410128 == 0) || (DAT_00410120 != 0xb7)) && (DAT_00410120 != 5)) {
    CreateMutexW((LPSECURITY_ATTRIBUTES)0x0,1,L"Global\\{154D96E8-CC81-4efb-91E0-A9E0EAAC6436}");
    HVar1 = CoInitializeEx((LPVOID)0x0,2);
    if (-1 < HVar1) {
      HVar1 = FUN_00408398();
      if (-1 < HVar1) {
        FUN_00408208();
        do {
          BVar2 = GetMessageW(&local_38,(HWND)0x0,0,0);
          if (BVar2 == -1) break;
          TranslateMessage(&local_38);
          DispatchMessageW(&local_38);
        } while (BVar2 != 0);
        FUN_00408208();
        FUN_00408208();
        if (DAT_004106c0 != (undefined8 *)0x0) {
          (**(code **)*DAT_004106c0)(DAT_004106c0,1);
          DAT_004106c0 = (undefined8 *)0x0;
        }
        HVar1 = 0;
      }
    }
    FUN_00408208();
    if (-1 < HVar1) {
      CoUninitialize();
    }
    uVar3 = 1;
  }
  else {
    FUN_00408208();
    uVar3 = 0;
  }
  return uVar3;
}



/* === FUN_00408398 @ 00408398 === */

int FUN_00408398(void)

{
  HRESULT HVar1;
  longlong *plVar2;
  undefined **ppuVar3;
  longlong *local_res8;
  
  FUN_00408208();
  local_res8 = (longlong *)0x0;
  HVar1 = CoCreateInstance((IID *)&DAT_00401318,(LPUNKNOWN)0x0,5,(IID *)&DAT_00401730,&local_res8);
  if (HVar1 < 0) {
    FUN_00408208();
    HVar1 = CoCreateInstance((IID *)&DAT_00401328,(LPUNKNOWN)0x0,5,(IID *)&DAT_00401730,&local_res8)
    ;
    if (HVar1 < 0) {
      FUN_00408208();
      goto LAB_004084b9;
    }
    FUN_00408208();
    plVar2 = LocalAlloc(0x40,0x88);
    if (plVar2 != (longlong *)0x0) {
      FUN_00408504(plVar2);
      ppuVar3 = &PTR_FUN_00403060;
      goto LAB_0040841e;
    }
  }
  else {
    FUN_00408208();
    plVar2 = LocalAlloc(0x40,0x88);
    if (plVar2 != (longlong *)0x0) {
      FUN_00408504(plVar2);
      ppuVar3 = &PTR_FUN_00402e40;
LAB_0040841e:
      *plVar2 = (longlong)ppuVar3;
      FUN_00408208();
      DAT_004106c0 = plVar2;
      goto LAB_004084b9;
    }
  }
  DAT_004106c0 = (longlong *)0x0;
LAB_004084b9:
  if (-1 < HVar1) {
    if (DAT_004106c0 == (longlong *)0x0) {
      FUN_00408208();
      HVar1 = -0x7ff8fff2;
    }
    else {
      HVar1 = (**(code **)(*DAT_004106c0 + 8))(DAT_004106c0,local_res8);
    }
    (**(code **)(*local_res8 + 0x10))();
  }
  return HVar1;
}



/* === FUN_00408504 @ 00408504 === */

undefined8 * FUN_00408504(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00402bd0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[9] = &PTR_FUN_004034b0;
  param_1[0xd] = &PTR_FUN_004034b0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  FUN_00408208();
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return param_1;
}



/* === FUN_00408588 @ 00408588 === */

undefined8 * FUN_00408588(undefined8 *param_1,uint param_2)

{
  FUN_004085c4(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_004085c4 @ 004085c4 === */

void FUN_004085c4(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00402bd0;
  FUN_00408208();
  FUN_0040926c((longlong)param_1);
  FUN_00409a2c(param_1 + 0xd);
  FUN_00409a2c(param_1 + 9);
  return;
}



/* === FUN_00408608 @ 00408608 === */

int FUN_00408608(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  int iVar2;
  HANDLE pvVar3;
  undefined8 *puVar4;
  longlong *local_res8;
  longlong *local_res18 [2];
  
  FUN_00408208();
  iVar2 = -0x7fffbffb;
  pvVar3 = CreateEventW((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCWSTR)0x0);
  param_1[6] = (longlong)pvVar3;
  if (pvVar3 == (HANDLE)0x0) goto LAB_00408896;
  FUN_00408208();
  pvVar3 = CreateWaitableTimerW((LPSECURITY_ATTRIBUTES)0x0,0,(LPCWSTR)0x0);
  param_1[7] = (longlong)pvVar3;
  if (pvVar3 == (HANDLE)0x0) goto LAB_00408896;
  FUN_00408208();
  pvVar3 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_004089a8,param_1,0,(LPDWORD)(param_1 + 8));
  param_1[5] = (longlong)pvVar3;
  if (pvVar3 == (HANDLE)0x0) goto LAB_00408896;
  FUN_00408208();
  iVar2 = (**(code **)(param_1[9] + 8))(param_1 + 9);
  if (iVar2 < 0) goto LAB_00408896;
  (**(code **)(param_1[9] + 0x40))(param_1 + 9,FUN_00408b00);
  iVar2 = (**(code **)(param_1[0xd] + 8))(param_1 + 0xd);
  if (iVar2 < 0) goto LAB_00408896;
  (**(code **)(param_1[0xd] + 0x40))(param_1 + 0xd,FUN_00408b00);
  if (param_2 != (longlong *)0x0) {
    param_1[1] = (longlong)param_2;
    (**(code **)(*param_2 + 8))(param_2);
    FUN_00408208();
    puVar4 = LocalAlloc(0x40,0x20);
    if (puVar4 == (undefined8 *)0x0) {
      puVar4 = (undefined8 *)0x0;
    }
    else {
      *puVar4 = &PTR_FUN_00403470;
      FUN_00408208();
      puVar4[1] = 0;
      puVar4[2] = 0;
      *(undefined4 *)(puVar4 + 3) = 0;
    }
    param_1[3] = (longlong)puVar4;
    if (puVar4 != (undefined8 *)0x0) {
      FUN_00408208();
      (**(code **)(*(longlong *)param_1[3] + 8))();
      lVar1 = param_1[3];
      FUN_00408208();
      *(code **)(lVar1 + 8) = FUN_004088b4;
      *(longlong **)(lVar1 + 0x10) = param_1;
      iVar2 = 0;
      local_res18[0] = (longlong *)0x0;
      (*(code *)**(undefined8 **)param_1[1])((undefined8 *)param_1[1],&DAT_00402c50,local_res18);
      if (local_res18[0] != (longlong *)0x0) {
        FUN_00408208();
        param_1[2] = (longlong)local_res18[0];
        (**(code **)(*local_res18[0] + 8))();
        local_res8 = (longlong *)0x0;
        (*(code *)**(undefined8 **)param_1[3])((undefined8 *)param_1[3],&DAT_00402c60,&local_res8);
        if (local_res8 == (longlong *)0x0) {
          FUN_00408208();
        }
        else {
          FUN_00408208();
          iVar2 = (**(code **)(*(longlong *)param_1[2] + 0x18))
                            ((longlong *)param_1[2],param_1,param_1 + 4,local_res8);
          if (-1 < iVar2) {
            (**(code **)(*param_1 + 0x30))(param_1);
          }
          (**(code **)(*local_res8 + 0x10))();
          local_res8 = (longlong *)0x0;
        }
        (**(code **)(*local_res18[0] + 0x10))();
        goto LAB_00408892;
      }
    }
    FUN_00408208();
  }
LAB_00408892:
  if (-1 < iVar2) {
    return iVar2;
  }
LAB_00408896:
  FUN_004093f4((longlong)param_1);
  return iVar2;
}



/* === FUN_004088b4 @ 004088b4 === */

void FUN_004088b4(longlong *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined8 param_5)

{
  FUN_00408208();
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x10))(param_1,param_2,param_3,param_4,param_5);
  }
  return;
}



/* === FUN_00408920 @ 00408920 === */

void FUN_00408920(longlong param_1,int param_2,int param_3)

{
  LARGE_INTEGER local_18 [2];
  
  FUN_00408208();
  if ((param_2 == 0x845) && (param_3 == -0x3fffdaff)) {
    FUN_00408208();
    local_18[0].QuadPart = -20000000;
    SetWaitableTimer(*(HANDLE *)(param_1 + 0x38),local_18,0,(PTIMERAPCROUTINE)0x0,(LPVOID)0x0,0);
  }
  return;
}



/* === FUN_004089a8 @ 004089a8 === */

undefined8 FUN_004089a8(longlong *param_1)

{
  bool bVar1;
  HRESULT HVar2;
  DWORD DVar3;
  HANDLE local_18;
  longlong local_10;
  
  FUN_00408208();
  HVar2 = CoInitializeEx((LPVOID)0x0,2);
  if ((param_1 != (longlong *)0x0) && (-1 < HVar2)) {
    local_18 = (HANDLE)param_1[6];
    bVar1 = true;
    local_10 = param_1[7];
    do {
      FUN_00408208();
      DVar3 = WaitForMultipleObjects(2,&local_18,0,0xffffffff);
      if ((DVar3 == 0) || (DVar3 == 0xffffffff)) {
        FUN_00408208();
        bVar1 = false;
      }
      else if (DVar3 == 1) {
        FUN_00408208();
        CancelWaitableTimer((HANDLE)param_1[7]);
        (**(code **)(*param_1 + 0x30))(param_1);
      }
    } while (bVar1);
  }
  FUN_00408208();
  if (-1 < HVar2) {
    CoUninitialize();
  }
  return 0;
}



/* === FUN_00408a88 @ 00408a88 === */

void FUN_00408a88(longlong param_1,undefined8 param_2)

{
  FUN_00408208();
                    /* WARNING: Could not recover jumptable at 0x00408ab8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(longlong *)(param_1 + 0x68) + 0x20))((longlong *)(param_1 + 0x68),param_2);
  return;
}



/* === FUN_00408ac4 @ 00408ac4 === */

void FUN_00408ac4(longlong param_1,undefined8 param_2)

{
  FUN_00408208();
                    /* WARNING: Could not recover jumptable at 0x00408af4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(longlong *)(param_1 + 0x48) + 0x20))((longlong *)(param_1 + 0x48),param_2);
  return;
}



/* === FUN_00408b00 @ 00408b00 === */

undefined8 FUN_00408b00(wchar_t *param_1,longlong param_2)

{
  int iVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if (((param_2 != 0) && (param_1 != (wchar_t *)0x0)) &&
     (*(wchar_t **)(param_2 + 8) != (wchar_t *)0x0)) {
    iVar1 = wcscoll(param_1,*(wchar_t **)(param_2 + 8));
    uVar2 = 0;
    if (iVar1 == 0) {
      uVar2 = 1;
    }
  }
  return uVar2;
}



/* === FUN_00408b38 @ 00408b38 === */

undefined8 FUN_00408b38(longlong param_1,longlong *param_2)

{
  longlong *plVar1;
  undefined8 uVar2;
  
  plVar1 = *(longlong **)(param_1 + 8);
  uVar2 = 0x80004005;
  if (plVar1 != (longlong *)0x0) {
    *param_2 = (longlong)plVar1;
    (**(code **)(*plVar1 + 8))();
    uVar2 = 0;
  }
  return uVar2;
}



/* === FUN_00408b60 @ 00408b60 === */

void FUN_00408b60(longlong *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong *local_res10;
  longlong *local_res18;
  
  FUN_00408208();
  local_res10 = (longlong *)0x0;
  local_res18 = (longlong *)0x0;
  iVar3 = 0;
  do {
    FUN_00408208();
    iVar1 = (**(code **)(*(longlong *)param_1[1] + 0x18))
                      ((longlong *)param_1[1],iVar3,2,0xf,&local_res10);
    if (iVar1 < 0) {
      FUN_00408208();
    }
    else {
      iVar2 = (**(code **)(*param_1 + 0x40))(param_1,local_res10);
      if (iVar2 == 0) {
        iVar2 = (**(code **)(*local_res10 + 0x30))(local_res10,&local_res18);
        if (-1 < iVar2) {
          iVar2 = (**(code **)(*param_1 + 0x48))(param_1,local_res18);
          if (iVar2 < 0) {
            FUN_00408208();
          }
          (**(code **)(*local_res18 + 0x10))();
          local_res18 = (longlong *)0x0;
        }
      }
      else if (iVar2 != 1) {
        FUN_00408208();
      }
      (**(code **)(*local_res10 + 0x10))();
      local_res10 = (longlong *)0x0;
    }
    iVar3 = iVar3 + 1;
  } while (-1 < iVar1);
  return;
}



/* === FUN_00408c74 @ 00408c74 === */

int FUN_00408c74(longlong *param_1,longlong *param_2)

{
  int iVar1;
  int iVar2;
  undefined8 *puVar3;
  longlong *local_res10;
  
  FUN_00408208();
  local_res10 = (longlong *)0x0;
  iVar1 = (**(code **)(*param_2 + 0x28))(param_2,&LAB_00402c70,&local_res10);
  if (local_res10 != (longlong *)0x0) {
    FUN_00408208();
    iVar2 = (**(code **)(*param_1 + 0x68))(param_1,param_2);
    if (iVar2 != 0) {
      puVar3 = (undefined8 *)(**(code **)(*param_1 + 0x50))(param_1,param_2);
      if (puVar3 == (undefined8 *)0x0) {
        iVar1 = -0x7fffbffb;
      }
      else {
        iVar1 = (**(code **)(*param_1 + 0x78))(param_1,puVar3,param_2);
        if (iVar1 < 0) {
          (**(code **)*puVar3)(puVar3,1);
        }
      }
    }
    (**(code **)(*local_res10 + 0x10))();
  }
  return iVar1;
}



/* === FUN_00408d44 @ 00408d44 === */

int FUN_00408d44(longlong *param_1,longlong *param_2)

{
  int iVar1;
  int iVar2;
  undefined8 *puVar3;
  longlong *local_res10;
  
  FUN_00408208();
  local_res10 = (longlong *)0x0;
  iVar1 = (**(code **)(*param_2 + 0x20))(param_2,&LAB_00402c70,&local_res10);
  if (local_res10 != (longlong *)0x0) {
    FUN_00408208();
    iVar2 = (**(code **)(*param_1 + 0x60))(param_1,param_2);
    if (iVar2 != 0) {
      FUN_00408208();
      puVar3 = (undefined8 *)(**(code **)(*param_1 + 0x58))(param_1,param_2);
      if (puVar3 == (undefined8 *)0x0) {
        iVar1 = -0x7fffbffb;
      }
      else {
        FUN_00408208();
        iVar1 = (**(code **)(*param_1 + 0x70))(param_1,puVar3,param_2);
        if (iVar1 < 0) {
          (**(code **)*puVar3)(puVar3,1);
        }
      }
    }
    (**(code **)(*local_res10 + 0x10))();
  }
  return iVar1;
}



/* === FUN_00408e2c @ 00408e2c === */

longlong * FUN_00408e2c(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  
  FUN_00408208();
  puVar2 = LocalAlloc(0x40,0x80);
  if (puVar2 == (undefined8 *)0x0) {
    plVar3 = (longlong *)0x0;
  }
  else {
    plVar3 = FUN_0040a41c(puVar2);
  }
  if (plVar3 != (longlong *)0x0) {
    iVar1 = (**(code **)(*plVar3 + 0x30))(plVar3,param_1,param_2);
    if (iVar1 < 0) {
      (**(code **)*plVar3)(plVar3,1);
      plVar3 = (longlong *)0x0;
    }
  }
  return plVar3;
}



/* === FUN_00408eb0 @ 00408eb0 === */

longlong * FUN_00408eb0(longlong param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  
  FUN_00408208();
  puVar2 = LocalAlloc(0x40,0x80);
  if (puVar2 == (undefined8 *)0x0) {
    plVar3 = (longlong *)0x0;
  }
  else {
    plVar3 = FUN_0040b93c(puVar2);
  }
  if (plVar3 != (longlong *)0x0) {
    iVar1 = (**(code **)(*plVar3 + 0x30))(plVar3,param_1,*(undefined8 *)(param_1 + 8),param_2);
    if (iVar1 < 0) {
      (**(code **)*plVar3)(plVar3,1);
      plVar3 = (longlong *)0x0;
    }
  }
  return plVar3;
}



/* === FUN_00408f38 @ 00408f38 === */

bool FUN_00408f38(longlong param_1,longlong *param_2)

{
  int iVar1;
  bool bVar2;
  undefined4 local_res10 [2];
  LPVOID local_res18;
  
  FUN_00408208();
  bVar2 = false;
  if (param_2 != (longlong *)0x0) {
    local_res18 = (LPVOID)0x0;
    local_res10[0] = 0;
    iVar1 = (**(code **)(*param_2 + 0x28))(param_2,local_res10,&local_res18);
    if (-1 < iVar1) {
      FUN_00408208();
      iVar1 = (**(code **)(*(longlong *)(param_1 + 0x68) + 0x18))
                        ((longlong *)(param_1 + 0x68),local_res18);
      bVar2 = iVar1 == 0;
      CoTaskMemFree(local_res18);
    }
  }
  FUN_00408208();
  return bVar2;
}



/* === FUN_00408fec @ 00408fec === */

bool FUN_00408fec(longlong param_1,longlong *param_2)

{
  int iVar1;
  bool bVar2;
  undefined4 local_res10 [2];
  LPVOID local_res18;
  
  FUN_00408208();
  bVar2 = false;
  if (param_2 != (longlong *)0x0) {
    local_res18 = (LPVOID)0x0;
    local_res10[0] = 0;
    iVar1 = (**(code **)(*param_2 + 0x18))(param_2,local_res10,&local_res18);
    if (-1 < iVar1) {
      FUN_00408208();
      iVar1 = (**(code **)(*(longlong *)(param_1 + 0x48) + 0x18))
                        ((longlong *)(param_1 + 0x48),local_res18);
      bVar2 = iVar1 == 0;
      CoTaskMemFree(local_res18);
    }
  }
  FUN_00408208();
  return bVar2;
}



/* === FUN_004090a0 @ 004090a0 === */

int FUN_004090a0(longlong param_1,undefined8 param_2,longlong *param_3)

{
  int iVar1;
  undefined8 *hMem;
  undefined4 local_res18 [2];
  LPVOID local_res20;
  
  FUN_00408208();
  iVar1 = -0x7fffbffb;
  if (param_3 != (longlong *)0x0) {
    local_res20 = (LPVOID)0x0;
    local_res18[0] = 0;
    hMem = LocalAlloc(0x40,0x10);
    if (hMem != (undefined8 *)0x0) {
      FUN_00408208();
      iVar1 = (**(code **)(*param_3 + 0x28))(param_3,local_res18,&local_res20);
      if (-1 < iVar1) {
        FUN_00408208();
        *hMem = param_2;
        hMem[1] = local_res20;
        iVar1 = (**(code **)(*(longlong *)(param_1 + 0x68) + 0x10))
                          ((longlong *)(param_1 + 0x68),hMem);
        if (iVar1 < 0) {
          CoTaskMemFree(local_res20);
          local_res20 = (LPVOID)0x0;
          LocalFree(hMem);
        }
      }
    }
  }
  return iVar1;
}



/* === FUN_00409188 @ 00409188 === */

int FUN_00409188(longlong param_1,undefined8 param_2,longlong *param_3)

{
  int iVar1;
  undefined8 *hMem;
  undefined4 local_res18 [2];
  LPVOID local_res20;
  
  FUN_00408208();
  iVar1 = -0x7fffbffb;
  if (param_3 != (longlong *)0x0) {
    local_res20 = (LPVOID)0x0;
    local_res18[0] = 0;
    hMem = LocalAlloc(0x40,0x10);
    if (hMem != (undefined8 *)0x0) {
      FUN_00408208();
      iVar1 = (**(code **)(*param_3 + 0x18))(param_3,local_res18,&local_res20);
      if (-1 < iVar1) {
        FUN_00408208();
        *hMem = param_2;
        hMem[1] = local_res20;
        iVar1 = (**(code **)(*(longlong *)(param_1 + 0x48) + 0x10))
                          ((longlong *)(param_1 + 0x48),hMem);
        if (iVar1 < 0) {
          CoTaskMemFree(local_res20);
          local_res20 = (LPVOID)0x0;
          LocalFree(hMem);
        }
      }
    }
  }
  return iVar1;
}



/* === FUN_0040926c @ 0040926c === */

void FUN_0040926c(longlong param_1)

{
  longlong lVar1;
  uint uVar2;
  longlong *plVar3;
  longlong *hMem;
  ulonglong uVar4;
  
  FUN_00408208();
  FUN_004093f4(param_1);
  lVar1 = *(longlong *)(param_1 + 0x18);
  if (lVar1 != 0) {
    FUN_00408208();
    *(undefined8 *)(lVar1 + 8) = 0;
    *(undefined8 *)(lVar1 + 0x10) = 0;
    (**(code **)(**(longlong **)(param_1 + 0x18) + 0x10))();
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  plVar3 = *(longlong **)(param_1 + 0x10);
  if (plVar3 != (longlong *)0x0) {
    (**(code **)(*plVar3 + 0x28))(plVar3,*(undefined4 *)(param_1 + 0x20));
    (**(code **)(**(longlong **)(param_1 + 0x10) + 0x10))();
    *(undefined8 *)(param_1 + 0x10) = 0;
  }
  if (*(longlong **)(param_1 + 8) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
    *(undefined8 *)(param_1 + 8) = 0;
  }
  uVar2 = (**(code **)(*(longlong *)(param_1 + 0x68) + 0x28))(param_1 + 0x68);
  if (uVar2 != 0) {
    uVar4 = (ulonglong)uVar2;
    do {
      plVar3 = (longlong *)(**(code **)(*(longlong *)(param_1 + 0x68) + 0x38))(param_1 + 0x68,0);
      if (plVar3 != (longlong *)0x0) {
        (**(code **)(*(longlong *)(param_1 + 0x68) + 0x20))(param_1 + 0x68);
        if ((LPVOID)plVar3[1] != (LPVOID)0x0) {
          CoTaskMemFree((LPVOID)plVar3[1]);
          plVar3[1] = 0;
        }
        if ((undefined8 *)*plVar3 != (undefined8 *)0x0) {
          (*(code *)**(undefined8 **)*plVar3)();
          *plVar3 = 0;
        }
        LocalFree(plVar3);
      }
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  plVar3 = (longlong *)(param_1 + 0x48);
  uVar2 = (**(code **)(*plVar3 + 0x28))(plVar3);
  if (uVar2 != 0) {
    uVar4 = (ulonglong)uVar2;
    do {
      hMem = (longlong *)(**(code **)(*plVar3 + 0x38))(plVar3,0);
      if (hMem != (longlong *)0x0) {
        (**(code **)(*plVar3 + 0x20))(plVar3);
        if ((LPVOID)hMem[1] != (LPVOID)0x0) {
          CoTaskMemFree((LPVOID)hMem[1]);
          hMem[1] = 0;
        }
        if ((undefined8 *)*hMem != (undefined8 *)0x0) {
          (*(code *)**(undefined8 **)*hMem)();
          *hMem = 0;
        }
        LocalFree(hMem);
      }
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  return;
}



/* === FUN_004093f4 @ 004093f4 === */

void FUN_004093f4(longlong param_1)

{
  FUN_00408208();
  if (*(longlong *)(param_1 + 0x30) != 0) {
    if (*(HANDLE *)(param_1 + 0x38) != (HANDLE)0x0) {
      CancelWaitableTimer(*(HANDLE *)(param_1 + 0x38));
      if (*(longlong *)(param_1 + 0x28) != 0) {
        SetEvent(*(HANDLE *)(param_1 + 0x30));
        WaitForSingleObject(*(HANDLE *)(param_1 + 0x28),0xffffffff);
        CloseHandle(*(HANDLE *)(param_1 + 0x28));
        *(undefined8 *)(param_1 + 0x28) = 0;
      }
      CloseHandle(*(HANDLE *)(param_1 + 0x38));
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    CloseHandle(*(HANDLE *)(param_1 + 0x30));
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  return;
}



/* === FUN_00409478 @ 00409478 === */

undefined8 * FUN_00409478(undefined8 *param_1,uint param_2)

{
  FUN_004094b4(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_004094b4 @ 004094b4 === */

void FUN_004094b4(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00402e40;
  FUN_00408208();
  FUN_004085c4(param_1);
  return;
}



/* === FUN_004094e8 @ 004094e8 === */

longlong * FUN_004094e8(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  longlong *plVar2;
  
  FUN_00408208();
  plVar2 = LocalAlloc(0x40,0x80);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)0x0;
  }
  else {
    FUN_0040a41c(plVar2);
    *plVar2 = (longlong)&PTR_FUN_00405730;
    FUN_00408208();
  }
  if (plVar2 != (longlong *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x30))(plVar2,param_1,param_2);
    if (iVar1 < 0) {
      (**(code **)*plVar2)(plVar2,1);
      plVar2 = (longlong *)0x0;
    }
  }
  return plVar2;
}



/* === FUN_00409584 @ 00409584 === */

longlong * FUN_00409584(longlong param_1,undefined8 param_2)

{
  int iVar1;
  longlong *plVar2;
  
  FUN_00408208();
  plVar2 = LocalAlloc(0x40,0x80);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)0x0;
  }
  else {
    FUN_0040b93c(plVar2);
    *plVar2 = (longlong)&PTR_FUN_00407f20;
    FUN_00408208();
  }
  if (plVar2 != (longlong *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x30))(plVar2,param_1,*(undefined8 *)(param_1 + 8),param_2);
    if (iVar1 < 0) {
      (**(code **)*plVar2)(plVar2,1);
      plVar2 = (longlong *)0x0;
    }
  }
  return plVar2;
}



/* === FUN_00409624 @ 00409624 === */

undefined8 * FUN_00409624(undefined8 *param_1,uint param_2)

{
  FUN_00409660(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_00409660 @ 00409660 === */

void FUN_00409660(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00403060;
  FUN_00408208();
  FUN_004085c4(param_1);
  return;
}



/* === FUN_00409694 @ 00409694 === */

longlong * FUN_00409694(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  longlong *plVar2;
  
  FUN_00408208();
  plVar2 = LocalAlloc(0x40,0x80);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)0x0;
  }
  else {
    FUN_0040a41c(plVar2);
    *plVar2 = (longlong)&PTR_FUN_00405870;
    FUN_00408208();
  }
  if (plVar2 != (longlong *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x30))(plVar2,param_1,param_2);
    if (iVar1 < 0) {
      (**(code **)*plVar2)(plVar2,1);
      plVar2 = (longlong *)0x0;
    }
  }
  return plVar2;
}



/* === FUN_00409730 @ 00409730 === */

longlong * FUN_00409730(longlong param_1,undefined8 param_2)

{
  int iVar1;
  longlong *plVar2;
  
  FUN_00408208();
  plVar2 = LocalAlloc(0x40,0x80);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)0x0;
  }
  else {
    FUN_0040b93c(plVar2);
    *plVar2 = (longlong)&PTR_FUN_004080e0;
    FUN_00408208();
  }
  if (plVar2 != (longlong *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x30))(plVar2,param_1,*(undefined8 *)(param_1 + 8),param_2);
    if (iVar1 < 0) {
      (**(code **)*plVar2)(plVar2,1);
      plVar2 = (longlong *)0x0;
    }
  }
  return plVar2;
}



/* === FUN_004097d0 @ 004097d0 === */

undefined8 * FUN_004097d0(undefined8 *param_1,uint param_2)

{
  *param_1 = &PTR_FUN_00403470;
  FUN_00408208();
  if ((param_2 & 1) != 0) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_0040981c @ 0040981c === */

undefined8 FUN_0040981c(longlong *param_1,ulonglong *param_2,undefined8 *param_3)

{
  int iVar1;
  bool bVar2;
  
  FUN_00408208();
  bVar2 = *param_2 < DAT_00403498;
  if ((*param_2 == DAT_00403498) && (bVar2 = param_2[1] < DAT_004034a0, param_2[1] == DAT_004034a0))
  {
    iVar1 = 0;
  }
  else {
    iVar1 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
  }
  if (iVar1 != 0) {
    bVar2 = *param_2 < DAT_00402c60;
    if ((*param_2 == DAT_00402c60) &&
       (bVar2 = param_2[1] < DAT_00402c68, param_2[1] == DAT_00402c68)) {
      iVar1 = 0;
    }
    else {
      iVar1 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
    }
    if (iVar1 != 0) {
      *param_3 = 0;
      return 0x80004002;
    }
  }
  *param_3 = param_1;
  (**(code **)(*param_1 + 8))(param_1);
  return 0;
}



/* === FUN_004098c8 @ 004098c8 === */

int FUN_004098c8(longlong param_1)

{
  int *piVar1;
  int iVar2;
  
  FUN_00408208();
  LOCK();
  piVar1 = (int *)(param_1 + 0x18);
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + 1;
  UNLOCK();
  return iVar2 + 1;
}



/* === FUN_00409900 @ 00409900 === */

int FUN_00409900(longlong *param_1)

{
  longlong *plVar1;
  longlong lVar2;
  int iVar3;
  
  FUN_00408208();
  LOCK();
  plVar1 = param_1 + 3;
  lVar2 = *plVar1;
  *(int *)plVar1 = (int)*plVar1 + -1;
  UNLOCK();
  iVar3 = (int)lVar2 + -1;
  if (iVar3 == 0) {
    (**(code **)(*param_1 + 0x20))(param_1,(int)lVar2);
  }
  return iVar3;
}



/* === FUN_00409950 @ 00409950 === */

undefined8
FUN_00409950(longlong *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined8 param_5)

{
  undefined8 uVar1;
  longlong lVar2;
  
  lVar2 = param_1[1];
  uVar1 = param_5;
  FUN_00408208();
  if (param_1[1] != 0) {
    (**(code **)(*param_1 + 8))(param_1);
    (*(code *)param_1[1])(param_1[2],param_2,param_3,param_4,param_5,uVar1,lVar2);
    (**(code **)(*param_1 + 0x10))(param_1);
  }
  return 0;
}



/* === FUN_004099f0 @ 004099f0 === */

undefined8 * FUN_004099f0(undefined8 *param_1,uint param_2)

{
  FUN_00409a2c(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_00409a2c @ 00409a2c === */

void FUN_00409a2c(undefined8 *param_1)

{
  longlong lVar1;
  undefined8 *hMem;
  
  lVar1 = param_1[1];
  *param_1 = &PTR_FUN_004034b0;
  while (lVar1 != 0) {
    if (*(HLOCAL *)(param_1[1] + 8) != (HLOCAL)0x0) {
      LocalFree(*(HLOCAL *)(param_1[1] + 8));
    }
    hMem = (undefined8 *)param_1[1];
    param_1[1] = *hMem;
    if (hMem != (undefined8 *)0x0) {
      LocalFree(hMem);
    }
    lVar1 = param_1[1];
  }
  if ((HANDLE)param_1[2] != (HANDLE)0x0) {
    CloseHandle((HANDLE)param_1[2]);
    param_1[2] = 0;
  }
  return;
}



/* === FUN_00409a98 @ 00409a98 === */

undefined8 FUN_00409a98(longlong param_1)

{
  HANDLE pvVar1;
  undefined8 uVar2;
  
  pvVar1 = CreateMutexW((LPSECURITY_ATTRIBUTES)0x0,0,(LPCWSTR)0x0);
  *(HANDLE *)(param_1 + 0x10) = pvVar1;
  uVar2 = 0x80004005;
  if (pvVar1 != (HANDLE)0x0) {
    uVar2 = 0;
  }
  return uVar2;
}



/* === FUN_00409ad8 @ 00409ad8 === */

undefined8 FUN_00409ad8(longlong param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  
  uVar2 = 0x80004005;
  if (*(HANDLE *)(param_1 + 0x10) != (HANDLE)0x0) {
    WaitForSingleObject(*(HANDLE *)(param_1 + 0x10),0xffffffff);
    puVar1 = LocalAlloc(0x40,0x10);
    if (puVar1 == (undefined8 *)0x0) {
      uVar2 = 0x8007000e;
    }
    else {
      puVar1[1] = param_2;
      uVar2 = 0;
      *puVar1 = *(undefined8 *)(param_1 + 8);
      *(undefined8 **)(param_1 + 8) = puVar1;
    }
    ReleaseMutex(*(HANDLE *)(param_1 + 0x10));
  }
  return uVar2;
}



/* === FUN_00409b54 @ 00409b54 === */

undefined4 FUN_00409b54(longlong *param_1,undefined8 param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((HANDLE)param_1[2] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)param_1[2],0xffffffff);
    uVar1 = (**(code **)(*param_1 + 0x48))(param_1,param_2);
    ReleaseMutex((HANDLE)param_1[2]);
  }
  return uVar1;
}



/* === FUN_00409bb0 @ 00409bb0 === */

void FUN_00409bb0(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  int iVar2;
  longlong *hMem;
  longlong *plVar3;
  
  if ((param_2 != 0) && (*(HANDLE *)(param_1 + 0x10) != (HANDLE)0x0)) {
    WaitForSingleObject(*(HANDLE *)(param_1 + 0x10),0xffffffff);
    if (*(longlong **)(param_1 + 8) != (longlong *)0x0) {
      plVar1 = *(longlong **)(param_1 + 8);
      plVar3 = (longlong *)0x0;
      do {
        hMem = plVar1;
        if (*(code **)(param_1 + 0x18) != (code *)0x0) {
          iVar2 = (**(code **)(param_1 + 0x18))(param_2,hMem[1]);
          if (iVar2 == 0) goto LAB_00409c25;
          if (plVar3 != (longlong *)0x0) goto LAB_00409c4a;
          *(undefined8 *)(param_1 + 8) = **(undefined8 **)(param_1 + 8);
LAB_00409c50:
          LocalFree(hMem);
          break;
        }
        if (hMem[1] == param_2) {
          if (plVar3 == (longlong *)0x0) {
            *(undefined8 *)(param_1 + 8) = **(undefined8 **)(param_1 + 8);
          }
          else {
LAB_00409c4a:
            *plVar3 = *hMem;
          }
          goto LAB_00409c50;
        }
LAB_00409c25:
        plVar1 = (longlong *)*hMem;
        plVar3 = hMem;
      } while ((longlong *)*hMem != (longlong *)0x0);
    }
    ReleaseMutex(*(HANDLE *)(param_1 + 0x10));
  }
  return;
}



/* === FUN_00409c7c @ 00409c7c === */

int FUN_00409c7c(longlong param_1)

{
  int iVar1;
  undefined8 *puVar2;
  
  iVar1 = 0;
  if (*(HANDLE *)(param_1 + 0x10) != (HANDLE)0x0) {
    WaitForSingleObject(*(HANDLE *)(param_1 + 0x10),0xffffffff);
    for (puVar2 = *(undefined8 **)(param_1 + 8); puVar2 != (undefined8 *)0x0;
        puVar2 = (undefined8 *)*puVar2) {
      iVar1 = iVar1 + 1;
    }
    ReleaseMutex(*(HANDLE *)(param_1 + 0x10));
  }
  return iVar1;
}



/* === FUN_00409ccc @ 00409ccc === */

int FUN_00409ccc(longlong param_1,longlong param_2)

{
  int iVar1;
  int iVar2;
  longlong *plVar3;
  
  iVar2 = -1;
  if ((param_2 != 0) && (iVar2 = -1, *(HANDLE *)(param_1 + 0x10) != (HANDLE)0x0)) {
    WaitForSingleObject(*(HANDLE *)(param_1 + 0x10),0xffffffff);
    plVar3 = *(longlong **)(param_1 + 8);
    iVar2 = -1;
    if (plVar3 != (longlong *)0x0) {
      iVar1 = 0;
      do {
        iVar2 = iVar1;
        if (*(code **)(param_1 + 0x18) == (code *)0x0) {
          if (plVar3[1] == param_2) break;
        }
        else {
          iVar1 = (**(code **)(param_1 + 0x18))(param_2,plVar3[1]);
          if (iVar1 != 0) break;
        }
        plVar3 = (longlong *)*plVar3;
        iVar1 = iVar2 + 1;
        iVar2 = -1;
      } while (plVar3 != (longlong *)0x0);
    }
    ReleaseMutex(*(HANDLE *)(param_1 + 0x10));
  }
  return iVar2;
}



/* === FUN_00409d68 @ 00409d68 === */

ulonglong FUN_00409d68(longlong param_1,uint param_2)

{
  uint uVar1;
  ulonglong uVar3;
  undefined8 *puVar4;
  ulonglong uVar2;
  
  uVar3 = 0;
  if (*(HANDLE *)(param_1 + 0x10) != (HANDLE)0x0) {
    WaitForSingleObject(*(HANDLE *)(param_1 + 0x10),0xffffffff);
    puVar4 = *(undefined8 **)(param_1 + 8);
    uVar2 = uVar3;
    if (param_2 != 0) {
      do {
        if (puVar4 == (undefined8 *)0x0) goto LAB_00409db2;
        puVar4 = (undefined8 *)*puVar4;
        uVar1 = (int)uVar2 + 1;
        uVar2 = (ulonglong)uVar1;
      } while (uVar1 < param_2);
    }
    if (puVar4 != (undefined8 *)0x0) {
      uVar3 = puVar4[1];
    }
LAB_00409db2:
    ReleaseMutex(*(HANDLE *)(param_1 + 0x10));
  }
  return uVar3;
}



/* === FUN_00409de4 @ 00409de4 === */

undefined8 FUN_00409de4(longlong *param_1,longlong param_2)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
  uVar1 = 0;
  if (param_1[3] == 0) {
    if (param_2 != 0) {
      for (puVar2 = (undefined8 *)param_1[1]; puVar2 != (undefined8 *)0x0;
          puVar2 = (undefined8 *)*puVar2) {
        if (puVar2[1] == param_2) {
          return 1;
        }
      }
    }
  }
  else {
    uVar1 = (**(code **)(*param_1 + 0x50))();
  }
  return uVar1;
}



/* === FUN_00409e24 @ 00409e24 === */

undefined8 FUN_00409e24(longlong param_1,longlong param_2)

{
  int iVar1;
  undefined8 *puVar2;
  
  if (param_2 != 0) {
    for (puVar2 = *(undefined8 **)(param_1 + 8); puVar2 != (undefined8 *)0x0;
        puVar2 = (undefined8 *)*puVar2) {
      iVar1 = (**(code **)(param_1 + 0x18))(param_2,puVar2[1]);
      if (iVar1 != 0) {
        return 1;
      }
    }
  }
  return 0;
}



/* === FUN_00409e88 @ 00409e88 === */

undefined8 * FUN_00409e88(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00403d00;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = &PTR_FUN_004034b0;
  FUN_00408208();
  param_1[5] = 0;
  return param_1;
}



/* === FUN_00409ed8 @ 00409ed8 === */

undefined8 * FUN_00409ed8(undefined8 *param_1,uint param_2)

{
  FUN_00409f14(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_00409f14 @ 00409f14 === */

void FUN_00409f14(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00403d00;
  FUN_00408208();
  FUN_0040a2e0((longlong)param_1);
  FUN_00409a2c(param_1 + 1);
  return;
}



/* === FUN_00409f54 @ 00409f54 === */

void FUN_00409f54(longlong *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined8 param_5)

{
  FUN_00408208();
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 8))(param_1,param_2,param_3,param_4,param_5);
  }
  return;
}



/* === FUN_00409fc0 @ 00409fc0 === */

void FUN_00409fc0(undefined8 *param_1,int param_2,int param_3)

{
  FUN_00408208();
  if (param_2 == 0x80a) {
    if ((param_3 != -0x7fffffff) && (param_3 != -0x7ffffffb)) {
      return;
    }
  }
  else {
    if (param_2 != 0x844) {
      return;
    }
    if (param_3 != -0x3fffdbff) {
      return;
    }
  }
  FUN_00408208();
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}



/* === FUN_0040a060 @ 0040a060 === */

int FUN_0040a060(longlong *param_1,undefined8 param_2,undefined8 param_3)

{
  longlong lVar1;
  int iVar2;
  undefined8 *puVar3;
  
  FUN_00408208();
  iVar2 = (**(code **)(param_1[1] + 8))(param_1 + 1);
  if (-1 < iVar2) {
    (**(code **)(param_1[1] + 0x40))(param_1 + 1,0);
    puVar3 = LocalAlloc(0x40,0x20);
    if (puVar3 == (undefined8 *)0x0) {
      puVar3 = (undefined8 *)0x0;
    }
    else {
      *puVar3 = &PTR_FUN_00403470;
      FUN_00408208();
      puVar3[1] = 0;
      puVar3[2] = 0;
      *(undefined4 *)(puVar3 + 3) = 0;
    }
    param_1[5] = (longlong)puVar3;
    if (puVar3 == (undefined8 *)0x0) {
      FUN_00408208();
    }
    else {
      FUN_00408208();
      (**(code **)(*(longlong *)param_1[5] + 8))();
      lVar1 = param_1[5];
      FUN_00408208();
      *(code **)(lVar1 + 8) = FUN_00409f54;
      *(longlong **)(lVar1 + 0x10) = param_1;
      iVar2 = (**(code **)(*param_1 + 0x18))(param_1,param_2);
      if (-1 < iVar2) {
        iVar2 = (**(code **)(*param_1 + 0x18))(param_1,param_3);
      }
    }
  }
  return iVar2;
}



/* === FUN_0040a19c @ 0040a19c === */

int FUN_0040a19c(longlong param_1,longlong *param_2)

{
  int iVar1;
  undefined8 *hMem;
  longlong *local_res8;
  
  FUN_00408208();
  iVar1 = -0x7fffbffb;
  if ((*(longlong *)(param_1 + 0x28) != 0) && (param_2 != (longlong *)0x0)) {
    hMem = LocalAlloc(0x40,0x10);
    if (hMem == (undefined8 *)0x0) {
      FUN_00408208();
      iVar1 = -0x7ff8fff2;
    }
    else {
      FUN_00408208();
      *hMem = param_2;
      (**(code **)(*param_2 + 8))(param_2);
      local_res8 = (longlong *)0x0;
      iVar1 = (**(code **)**(undefined8 **)(param_1 + 0x28))
                        (*(undefined8 **)(param_1 + 0x28),&DAT_00402c60,&local_res8);
      if (iVar1 < 0) {
        FUN_00408208();
        LocalFree(hMem);
      }
      else {
        FUN_00408208();
        iVar1 = (**(code **)(*(longlong *)*hMem + 0x18))
                          ((longlong *)*hMem,param_1,hMem + 1,local_res8);
        if (iVar1 < 0) {
          (**(code **)(*(longlong *)*hMem + 0x10))();
          LocalFree(hMem);
        }
        else {
          (**(code **)(*(longlong *)(param_1 + 8) + 0x10))((longlong *)(param_1 + 8),hMem);
        }
        (**(code **)(*local_res8 + 0x10))();
      }
    }
  }
  return iVar1;
}



/* === FUN_0040a2e0 @ 0040a2e0 === */

void FUN_0040a2e0(longlong param_1)

{
  longlong lVar1;
  uint uVar2;
  longlong *hMem;
  ulonglong uVar3;
  
  FUN_00408208();
  uVar2 = (**(code **)(*(longlong *)(param_1 + 8) + 0x28))(param_1 + 8);
  if (uVar2 != 0) {
    uVar3 = (ulonglong)uVar2;
    do {
      hMem = (longlong *)(**(code **)(*(longlong *)(param_1 + 8) + 0x38))(param_1 + 8,0);
      if (hMem != (longlong *)0x0) {
        (**(code **)(*(longlong *)(param_1 + 8) + 0x20))(param_1 + 8);
        if ((longlong *)*hMem != (longlong *)0x0) {
          (**(code **)(*(longlong *)*hMem + 0x28))();
          (**(code **)(*(longlong *)*hMem + 0x10))();
        }
        LocalFree(hMem);
      }
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
  lVar1 = *(longlong *)(param_1 + 0x28);
  if (lVar1 != 0) {
    FUN_00408208();
    *(undefined8 *)(lVar1 + 8) = 0;
    *(undefined8 *)(lVar1 + 0x10) = 0;
    (**(code **)(**(longlong **)(param_1 + 0x28) + 0x10))();
    *(undefined8 *)(param_1 + 0x28) = 0;
  }
  return;
}



/* === FUN_0040a3b4 @ 0040a3b4 === */

void FUN_0040a3b4(undefined8 param_1,uint param_2)

{
  undefined1 auStackY_58 [32];
  wchar_t local_28 [12];
  ulonglong local_10;
  
  local_10 = DAT_00410108 ^ (ulonglong)auStackY_58;
  swprintf_s(local_28,0x14,L"/m=%d",(ulonglong)param_2);
  ShellExecuteW((HWND)0x0,(LPCWSTR)0x0,L"JDetect.exe",local_28,(LPCWSTR)0x0,1);
  FUN_0040eea0(local_10 ^ (ulonglong)auStackY_58);
  return;
}



/* === FUN_0040a41c @ 0040a41c === */

undefined8 * FUN_0040a41c(undefined8 *param_1)

{
  FUN_00409e88(param_1);
  *param_1 = &PTR_FUN_00405530;
  FUN_00408208();
  param_1[10] = 0;
  param_1[6] = 0;
  param_1[8] = 0;
  param_1[7] = 0;
  param_1[9] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xc] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  *(undefined4 *)(param_1 + 0xf) = 0;
  *(undefined4 *)((longlong)param_1 + 0x7c) = 0;
  return param_1;
}



/* === FUN_0040a484 @ 0040a484 === */

undefined8 * FUN_0040a484(undefined8 *param_1,uint param_2)

{
  FUN_0040a4c0(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_0040a4c0 @ 0040a4c0 === */

void FUN_0040a4c0(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00405530;
  FUN_00408208();
  FUN_0040b030((longlong)param_1);
  FUN_00409f14(param_1);
  return;
}



/* === FUN_0040a500 @ 0040a500 === */

void FUN_0040a500(longlong *param_1,longlong param_2,longlong *param_3)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  longlong *plVar4;
  short sVar5;
  undefined8 uVar6;
  bool bVar7;
  undefined1 auStack_e8 [32];
  short local_c8 [2];
  short local_c4 [2];
  longlong *local_c0;
  longlong *local_b8;
  undefined4 local_b0 [2];
  longlong *local_a8;
  longlong *local_a0;
  undefined4 local_98 [2];
  longlong *local_90;
  undefined4 local_88 [2];
  undefined4 local_80 [2];
  int local_78;
  undefined4 local_74;
  undefined4 local_70;
  ulonglong local_48;
  ulonglong local_40;
  ulonglong local_38;
  
  local_38 = DAT_00410108 ^ (ulonglong)auStack_e8;
  FUN_00408208();
  if (param_3 == (longlong *)0x0) goto LAB_0040a8fe;
  param_1[8] = param_2;
  local_90 = (longlong *)0x0;
  FUN_00408208();
  iVar1 = (**(code **)*param_3)(param_3,&DAT_00402c50,&local_90);
  iVar2 = 0;
  if (iVar1 < 0) goto LAB_0040a8fe;
  local_a8 = (longlong *)0x0;
  FUN_00408208();
  iVar1 = (**(code **)(*param_3 + 0x28))(param_3,&LAB_00402c70,&local_a8);
  if (-1 < iVar1) {
    FUN_00408208();
    local_a0 = (longlong *)0x0;
    iVar1 = (**(code **)*local_a8)(local_a8,&DAT_00402c50,&local_a0);
    if (-1 < iVar1) {
      FUN_00408208();
      iVar1 = FUN_0040a060(param_1,local_90,local_a0);
      if (-1 < iVar1) {
        param_1[6] = (longlong)param_3;
        (**(code **)(*param_3 + 8))(param_3);
        local_98[0] = 0;
        (**(code **)(*(longlong *)param_1[6] + 0x18))((longlong *)param_1[6],local_98,param_1 + 9);
        local_b8 = (longlong *)0x0;
        local_88[0] = 0;
        iVar1 = (**(code **)(*(longlong *)param_1[6] + 0x30))((longlong *)param_1[6],&local_b8);
        if (local_b8 != (longlong *)0x0) {
          (**(code **)(*local_b8 + 0x28))(local_b8,local_88,param_1 + 10);
          local_80[0] = 0x34;
          iVar1 = (**(code **)(*local_b8 + 0x18))(local_b8,local_80);
          if ((-1 < iVar1) && (local_78 == 0)) {
            *(undefined4 *)((longlong)param_1 + 0x7c) = local_74;
            *(undefined4 *)(param_1 + 0xf) = local_70;
          }
          (**(code **)(*local_b8 + 0x10))();
          local_b8 = (longlong *)0x0;
        }
        if (-1 < iVar1) {
          (**(code **)(*(longlong *)param_1[6] + 0x28))
                    ((longlong *)param_1[6],&DAT_00405588,param_1 + 0xd);
          (**(code **)(*(longlong *)param_1[6] + 0x20))((longlong *)param_1[6],&local_48);
          bVar7 = local_48 < DAT_00405598;
          if ((local_48 != DAT_00405598) ||
             (bVar7 = local_40 < DAT_004055a0, iVar1 = iVar2, local_40 != DAT_004055a0)) {
            iVar1 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          }
          if (iVar1 == 0) {
LAB_0040a755:
            iVar1 = (**(code **)(*(longlong *)param_1[6] + 0x28))
                              ((longlong *)param_1[6],&DAT_004055b8,param_1 + 0xe);
            if (-1 < iVar1) {
              local_c0 = (longlong *)0x0;
              FUN_00408208();
              iVar1 = (*(code *)**(undefined8 **)param_1[0xe])
                                ((undefined8 *)param_1[0xe],&DAT_00402c50,&local_c0);
              if (-1 < iVar1) {
                local_c4[0] = 0;
                local_c8[0] = 0;
                (**(code **)(*(longlong *)param_1[0xe] + 0x18))((longlong *)param_1[0xe],local_c4,1)
                ;
                (**(code **)(*(longlong *)param_1[0xe] + 0x18))((longlong *)param_1[0xe],local_c8,2)
                ;
                plVar4 = (longlong *)param_1[0xe];
                lVar3 = *plVar4;
                if (local_c4[0] == local_c8[0]) {
                  uVar6 = 0;
                  sVar5 = local_c4[0];
                }
                else {
                  (**(code **)(lVar3 + 0x20))(plVar4,local_c4[0],1);
                  plVar4 = (longlong *)param_1[0xe];
                  lVar3 = *plVar4;
                  uVar6 = 2;
                  sVar5 = local_c8[0];
                }
                (**(code **)(lVar3 + 0x20))(plVar4,sVar5,uVar6);
                local_b0[0] = 0;
                (**(code **)(*(longlong *)param_1[0xe] + 0x28))((longlong *)param_1[0xe],local_b0);
                (**(code **)(*(longlong *)param_1[0xe] + 0x30))
                          ((longlong *)param_1[0xe],local_b0[0]);
                (**(code **)(*param_1 + 0x18))(param_1,local_c0);
                (**(code **)(*local_c0 + 0x10))();
              }
            }
          }
          else {
            bVar7 = local_48 < DAT_004055a8;
            if ((local_48 != DAT_004055a8) ||
               (bVar7 = local_40 < DAT_004055b0, local_40 != DAT_004055b0)) {
              iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
            }
            if (iVar2 == 0) goto LAB_0040a755;
          }
          (**(code **)(*param_1 + 0x40))(param_1);
          (**(code **)(*param_1 + 0x50))(param_1);
          (**(code **)(*param_1 + 0x38))(param_1);
          iVar1 = (**(code **)(*(longlong *)param_1[6] + 0x28))
                            ((longlong *)param_1[6],&DAT_004055c8,param_1 + 0xc);
          if (-1 < iVar1) {
            local_c0 = (longlong *)0x0;
            FUN_00408208();
            iVar1 = (*(code *)**(undefined8 **)param_1[0xc])
                              ((undefined8 *)param_1[0xc],&DAT_00402c50,&local_c0);
            if (-1 < iVar1) {
              (**(code **)(*(longlong *)param_1[0xc] + 0x28))();
              (**(code **)(*param_1 + 0x18))(param_1,local_c0);
              (**(code **)(*local_c0 + 0x10))();
            }
          }
        }
      }
      (**(code **)(*local_a0 + 0x10))();
      local_a0 = (longlong *)0x0;
    }
    (**(code **)(*local_a8 + 0x10))();
    local_a8 = (longlong *)0x0;
  }
  (**(code **)(*local_90 + 0x10))();
LAB_0040a8fe:
  FUN_0040eea0(local_38 ^ (ulonglong)auStack_e8);
  return;
}



/* === FUN_0040a924 @ 0040a924 === */

void FUN_0040a924(longlong param_1)

{
  int iVar1;
  int local_res8 [2];
  longlong *local_res10;
  longlong *local_res18 [2];
  short local_28 [16];
  
  FUN_00408208();
  if (((*(longlong *)(param_1 + 0x68) != 0) &&
      (iVar1 = (**(code **)(**(longlong **)(param_1 + 0x68) + 0x18))
                         (*(longlong **)(param_1 + 0x68),0xe,local_res8), -1 < iVar1)) &&
     (local_res8[0] == 1)) {
    local_res18[0] = (longlong *)0x0;
    FUN_0040df78(0,*(short **)(param_1 + 0x48),local_res18);
    if (local_res18[0] != (longlong *)0x0) {
      local_28[0] = 0;
      local_28[1] = 0;
      local_28[2] = 0;
      local_28[3] = 0;
      local_28[4] = 0;
      local_28[5] = 0;
      local_28[6] = 0;
      local_28[7] = 0;
      local_28[8] = 0;
      local_28[9] = 0;
      local_28[10] = 0;
      local_28[0xb] = 0;
      iVar1 = (**(code **)(*local_res18[0] + 0x18))(local_res18[0],&DAT_00403110,local_28);
      if ((iVar1 < 0) || (local_28[0] != 0xb)) {
        PropVariantClear((PROPVARIANT *)local_28);
        local_res10 = (longlong *)0x0;
        (**(code **)**(undefined8 **)(param_1 + 0x30))
                  (*(undefined8 **)(param_1 + 0x30),&DAT_004055d8,&local_res10);
        if (local_res10 != (longlong *)0x0) {
          FUN_00408208();
          (**(code **)(*local_res10 + 0x18))();
          (**(code **)(*local_res10 + 0x10))();
          local_res10 = (longlong *)0x0;
        }
        local_28[8] = 0;
        local_28[9] = 0;
        local_28[10] = 0;
        local_28[0xb] = 0;
        local_28[0] = 0xb;
        local_28[1] = 0;
        local_28[2] = 0;
        local_28[3] = 0;
        local_28[4] = 1;
        local_28[5] = 0;
        local_28[6] = 0;
        local_28[7] = 0;
        (**(code **)(*local_res18[0] + 0x20))(local_res18[0],&DAT_00403110,local_28);
      }
      FUN_00408208();
      PropVariantClear((PROPVARIANT *)local_28);
      (**(code **)(*local_res18[0] + 0x10))();
    }
  }
  FUN_00408208();
  return;
}



/* === FUN_0040aaa0 @ 0040aaa0 === */

void FUN_0040aaa0(longlong *param_1,int param_2,int param_3)

{
  HRESULT HVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  short sVar6;
  int iVar7;
  undefined8 uVar8;
  uint local_res10 [2];
  undefined4 local_98;
  int local_94;
  uint local_90 [2];
  longlong *local_88;
  longlong *local_80;
  longlong *local_78;
  undefined4 local_70;
  int local_6c;
  wchar_t *local_68;
  LPVOID local_60;
  longlong *local_58;
  undefined4 local_50 [2];
  int local_48;
  int local_44;
  int local_40;
  
  FUN_00408208();
  if (param_2 == 0x10000001) {
    param_2 = 0x10000001;
    if (param_3 == -0x7fffffff) {
      FUN_00408208();
      if (param_1[0xd] == 0) {
        local_88 = (longlong *)0x0;
        local_50[0] = 0x34;
        if (param_1[6] != 0) {
          iVar7 = (**(code **)(*(longlong *)param_1[6] + 0x30))((longlong *)param_1[6],&local_88);
          if (iVar7 < 0) {
            return;
          }
          iVar7 = (**(code **)(*local_88 + 0x18))(local_88,local_50);
          if ((-1 < iVar7) && (local_48 == 0)) {
            if (((local_44 == 0x41e) && (local_40 == 0x30d2)) || (local_40 == 0x30e0)) {
              (**(code **)(*param_1 + 0x28))(param_1,1);
            }
            else if (((local_44 == 0x41e) && (local_40 == 0x3041)) || (local_40 == 0x3042)) {
              (**(code **)(*param_1 + 0x38))(param_1);
            }
          }
          (**(code **)(*local_88 + 0x10))();
          return;
        }
        lVar4 = *param_1;
      }
      else {
        FUN_00408208();
        local_res10[0] = 0;
        iVar7 = (**(code **)(*(longlong *)param_1[0xd] + 0x18))
                          ((longlong *)param_1[0xd],1,local_res10);
        FUN_00408208();
        lVar4 = *param_1;
        if ((-1 < iVar7) && (local_res10[0] != 0)) {
          (**(code **)(lVar4 + 0x28))(param_1,1);
          return;
        }
      }
      (**(code **)(lVar4 + 0x38))(param_1);
      return;
    }
  }
  else if (param_2 == 0x10000003) {
    if (param_1[0xe] != 0) {
      if (param_3 == -0x7fffffff) {
        local_98 = (uint)local_98._2_2_ << 0x10;
        local_res10[0] = local_res10[0] & 0xffff0000;
        (**(code **)(*(longlong *)param_1[0xe] + 0x18))((longlong *)param_1[0xe],&local_98,1);
        (**(code **)(*(longlong *)param_1[0xe] + 0x18))((longlong *)param_1[0xe],local_res10,2);
        plVar5 = (longlong *)param_1[0xe];
        lVar4 = *plVar5;
        if ((short)local_98 == (short)local_res10[0]) {
          uVar8 = 0;
          sVar6 = (short)local_98;
        }
        else {
          (**(code **)(lVar4 + 0x20))(plVar5,(short)local_98,1);
          plVar5 = (longlong *)param_1[0xe];
          lVar4 = *plVar5;
          uVar8 = 2;
          sVar6 = (short)local_res10[0];
        }
        (**(code **)(lVar4 + 0x20))(plVar5,sVar6,uVar8);
        return;
      }
      if (param_3 != -0x7ffffffe) {
        return;
      }
      local_res10[0] = 0;
      (**(code **)(*(longlong *)param_1[0xe] + 0x28))((longlong *)param_1[0xe],local_res10);
      (**(code **)(*(longlong *)param_1[0xe] + 0x30))((longlong *)param_1[0xe],local_res10[0]);
      return;
    }
    param_2 = 0x10000003;
  }
  else {
    if (param_2 == 0x10000004) {
      if (param_3 != -0x7fffffff) {
        return;
      }
      HVar1 = CoInitialize((LPVOID)0x0);
      FUN_00408208();
      iVar7 = 0;
      if (HVar1 < 0) {
        return;
      }
      local_res10[0] = 0x10;
      local_98 = 48000;
      iVar2 = (**(code **)(*(longlong *)param_1[0xc] + 0x18))
                        ((longlong *)param_1[0xc],&local_98,local_res10);
      FUN_00408208();
      if (-1 < iVar2) {
        local_58 = (longlong *)0x0;
        local_70 = 0;
        local_68 = (wchar_t *)0x0;
        local_60 = (LPVOID)0x0;
        local_80 = (longlong *)0x0;
        local_78 = (longlong *)0x0;
        local_88 = (longlong *)0x0;
        iVar2 = (**(code **)(*(longlong *)param_1[8] + 0x28))((longlong *)param_1[8],&local_88);
        if (-1 < iVar2) {
          do {
            iVar2 = (**(code **)(*local_88 + 0x18))(local_88,iVar7,2,0xf,&local_80);
            FUN_00408208();
            if (-1 < iVar2) {
              (**(code **)(*local_80 + 0x28))(local_80,&DAT_004055c8,&local_78);
              if (local_78 != (longlong *)0x0) {
                local_6c = 0;
                iVar2 = (**(code **)(*local_78 + 0x20))(local_78,&local_6c);
                if (local_6c == 0) {
LAB_0040adaf:
                  FUN_00408208();
                }
                else {
                  FUN_00408208();
                  local_94 = 48000;
                  local_90[0] = 0x10;
                  (**(code **)(*local_78 + 0x18))(local_78,&local_94,local_90);
                  FUN_00408208();
                  if ((local_94 == local_98) && (local_90[0] == local_res10[0])) goto LAB_0040adaf;
                  FUN_00408208();
                  (**(code **)(*local_80 + 0x30))(local_80,&local_58);
                  if (local_58 != (longlong *)0x0) {
                    (**(code **)(*local_58 + 0x28))(local_58,&local_70,&local_68);
                    iVar3 = wcscoll(local_68,(wchar_t *)param_1[10]);
                    if ((iVar3 == 0) &&
                       (iVar3 = (**(code **)(*local_80 + 0x18))(local_80,&local_70,&local_60),
                       -1 < iVar3)) {
                      FUN_00408208();
                      FUN_0040e1b0(local_60,local_98,(ushort)local_res10[0]);
                      CoTaskMemFree(local_60);
                      local_60 = (LPVOID)0x0;
                    }
                    CoTaskMemFree(local_68);
                    local_68 = (wchar_t *)0x0;
                    (**(code **)(*local_58 + 0x10))();
                    local_58 = (longlong *)0x0;
                  }
                }
                (**(code **)(*local_78 + 0x10))();
                local_78 = (longlong *)0x0;
              }
              (**(code **)(*local_80 + 0x10))();
              local_80 = (longlong *)0x0;
            }
            iVar7 = iVar7 + 1;
          } while (-1 < iVar2);
          (**(code **)(*local_88 + 0x10))();
        }
      }
      CoUninitialize();
      return;
    }
    if (param_2 == 0x10000050) {
      (**(code **)(*param_1 + 0x50))();
      return;
    }
  }
  FUN_00409fc0(param_1,param_2,param_3);
  return;
}



/* === FUN_0040b030 @ 0040b030 === */

void FUN_0040b030(longlong param_1)

{
  int iVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined4 local_res8 [2];
  LPVOID local_res10;
  
  FUN_00408208();
  if ((*(longlong *)(param_1 + 0x40) != 0) &&
     (plVar2 = *(longlong **)(param_1 + 0x30), plVar2 != (longlong *)0x0)) {
    local_res8[0] = 0;
    local_res10 = (LPVOID)0x0;
    (**(code **)(*plVar2 + 0x18))(plVar2,local_res8,&local_res10);
    if (local_res10 != (LPVOID)0x0) {
      iVar1 = (**(code **)(*(longlong *)(*(longlong *)(param_1 + 0x40) + 0x48) + 0x30))();
      if (iVar1 != -1) {
        plVar2 = (longlong *)(*(longlong *)(param_1 + 0x40) + 0x48);
        plVar2 = (longlong *)(**(code **)(*plVar2 + 0x38))(plVar2,iVar1);
        if (plVar2 != (longlong *)0x0) {
          plVar3 = (longlong *)(*(longlong *)(param_1 + 0x40) + 0x48);
          (**(code **)(*plVar3 + 0x20))(plVar3,local_res10);
          if ((LPVOID)plVar2[1] != (LPVOID)0x0) {
            CoTaskMemFree((LPVOID)plVar2[1]);
            plVar2[1] = 0;
          }
          if (*plVar2 != 0) {
            *plVar2 = 0;
          }
          LocalFree(plVar2);
        }
        CoTaskMemFree(local_res10);
      }
      *(undefined8 *)(param_1 + 0x40) = 0;
    }
    if (*(longlong **)(param_1 + 0x38) != (longlong *)0x0) {
      (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))();
      *(undefined8 *)(param_1 + 0x38) = 0;
    }
    if (*(LPVOID *)(param_1 + 0x48) != (LPVOID)0x0) {
      CoTaskMemFree(*(LPVOID *)(param_1 + 0x48));
      *(undefined8 *)(param_1 + 0x48) = 0;
    }
  }
  FUN_0040a2e0(param_1);
  if (*(LPVOID *)(param_1 + 0x50) != (LPVOID)0x0) {
    CoTaskMemFree(*(LPVOID *)(param_1 + 0x50));
    *(undefined8 *)(param_1 + 0x50) = 0;
  }
  if (*(longlong **)(param_1 + 0x30) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x30) + 0x10))();
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  if (*(longlong **)(param_1 + 0x68) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x68) + 0x10))();
    *(undefined8 *)(param_1 + 0x68) = 0;
  }
  if (*(longlong **)(param_1 + 0x70) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x70) + 0x10))();
    *(undefined8 *)(param_1 + 0x70) = 0;
  }
  if (*(longlong **)(param_1 + 0x60) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x60) + 0x30))();
    (**(code **)(**(longlong **)(param_1 + 0x60) + 0x10))();
    *(undefined8 *)(param_1 + 0x60) = 0;
  }
  return;
}



/* === FUN_0040b1b0 @ 0040b1b0 === */

void FUN_0040b1b0(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int local_res8 [2];
  int local_res10 [2];
  int local_res18 [2];
  undefined1 local_res20 [8];
  undefined4 uVar5;
  longlong *local_38;
  longlong *local_30;
  undefined8 local_28;
  longlong *local_20 [2];
  
  FUN_00408208();
  if (*(int *)(param_1 + 0x7c) == 0x41e) {
    if (*(int *)(param_1 + 0x78) == 0x323b) {
      return;
    }
    if (*(int *)(param_1 + 0x78) == 0x323e) {
      return;
    }
  }
  if (*(longlong **)(param_1 + 0x30) == (longlong *)0x0) {
    return;
  }
  (**(code **)(**(longlong **)(param_1 + 0x30) + 8))();
  local_30 = (longlong *)0x0;
  local_38 = (longlong *)0x0;
  local_20[0] = (longlong *)0x0;
  FUN_00408208();
  (**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))
            (*(longlong **)(param_1 + 0x30),&LAB_00402c70,&local_30);
  plVar1 = local_30;
  if (local_30 == (longlong *)0x0) goto LAB_0040b4fd;
  FUN_00408208();
  local_res10[0] = 0;
  iVar2 = (**(code **)(*plVar1 + 0x28))(plVar1,local_res10);
  if (-1 < iVar2) {
    FUN_00408208();
    FUN_00408208();
    (**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))
              (*(longlong **)(param_1 + 0x30),&DAT_004055e8,&local_38);
    if (local_38 != (longlong *)0x0) {
      local_res8[0] = 0;
      if (local_res10[0] == 0) {
        local_28 = 0;
        iVar2 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                          (*(longlong **)(param_1 + 0x30),local_res20,&local_28);
        if (-1 < iVar2) {
          local_res18[0] = 0;
          iVar2 = FUN_0040e0bc(local_28,local_res18);
          if (-1 < iVar2) {
            iVar2 = *(int *)(param_1 + 0x58);
            if (*(int *)(param_1 + 0x58) == 0) {
              (**(code **)(*local_38 + 0x40))(local_38,0,0,local_res8);
              *(int *)(param_1 + 0x58) = local_res8[0];
              iVar2 = local_res8[0];
            }
            local_res8[0] = iVar2;
            iVar2 = local_res18[0];
            FUN_00408208();
            if (iVar2 == 3) {
              FUN_00408208();
              puVar3 = &DAT_004012b8;
LAB_0040b474:
              uVar5 = 7;
              iVar4 = local_res8[0];
            }
            else {
              if (iVar2 == 0x33) {
                FUN_00408208();
                puVar3 = &DAT_004012d8;
                goto LAB_0040b474;
              }
              if (iVar2 == 0x60f) {
                FUN_00408208();
                puVar3 = &DAT_00401308;
                goto LAB_0040b474;
              }
              if (iVar2 == 0x3f) {
                FUN_00408208();
                puVar3 = &DAT_004012e8;
                goto LAB_0040b474;
              }
              if ((iVar2 == 0xff) || (iVar2 == 0x63f)) {
                FUN_00408208();
                puVar3 = &DAT_004012f8;
                goto LAB_0040b474;
              }
              FUN_00408208();
              iVar4 = 0;
              iVar2 = 0;
              uVar5 = 1;
              puVar3 = &DAT_004012b8;
            }
            (**(code **)(*local_38 + 0x48))(local_38,puVar3,iVar2,iVar4,uVar5);
          }
        }
      }
      else {
        (**(code **)(*local_38 + 0x40))(local_38,0,0,local_res8);
        *(int *)(param_1 + 0x58) = local_res8[0];
        (**(code **)(*local_38 + 0x48))(local_38,&DAT_004012c8,0,0,1);
        FUN_00408208();
      }
      (**(code **)(*local_38 + 0x10))();
      local_38 = (longlong *)0x0;
    }
    (**(code **)(**(longlong **)(param_1 + 0x30) + 0x28))
              (*(longlong **)(param_1 + 0x30),&DAT_004055f8,local_20);
    if (local_20[0] != (longlong *)0x0) {
      if (local_res10[0] == 0) {
        (**(code **)(*local_20[0] + 0x20))(local_20[0],0);
      }
      else {
        (**(code **)(*local_20[0] + 0x20))(local_20[0],2);
      }
      FUN_00408208();
    }
  }
  (**(code **)(*local_30 + 0x10))();
  local_30 = (longlong *)0x0;
LAB_0040b4fd:
  (**(code **)(**(longlong **)(param_1 + 0x30) + 0x10))();
  return;
}



/* === FUN_0040b514 @ 0040b514 === */

void FUN_0040b514(longlong *param_1)

{
  int iVar1;
  bool bVar2;
  undefined1 auStack_68 [32];
  short local_48 [4];
  undefined8 local_40;
  undefined8 local_38;
  longlong *local_30;
  undefined8 local_28;
  ulonglong local_20;
  ulonglong local_18;
  ulonglong local_10;
  
  local_10 = DAT_00410108 ^ (ulonglong)auStack_68;
  local_28 = 0;
  (**(code **)(*(longlong *)param_1[6] + 0x20))((longlong *)param_1[6],&local_20);
  bVar2 = local_20 < DAT_00405598;
  if ((local_20 == DAT_00405598) && (bVar2 = local_18 < DAT_004055a0, local_18 == DAT_004055a0)) {
    iVar1 = 0;
  }
  else {
    iVar1 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
  }
  if (iVar1 != 0) {
    bVar2 = local_20 < DAT_004055a8;
    if (local_20 == DAT_004055a8) {
      bVar2 = local_18 < DAT_004055b0;
      if (local_18 != DAT_004055b0) goto LAB_0040b595;
      iVar1 = 0;
    }
    else {
LAB_0040b595:
      iVar1 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
    }
    if (iVar1 != 0) goto LAB_0040b6ca;
  }
  (**(code **)(*param_1 + 0x48))(param_1);
  if (param_1[7] != 0) {
    (**(code **)(*(longlong *)param_1[7] + 0x18))((longlong *)param_1[7],&local_28);
    FUN_00408208();
    local_30 = (longlong *)0x0;
    FUN_0040df78(0,(short *)param_1[9],&local_30);
    if (local_30 != (longlong *)0x0) {
      local_48[0] = 0;
      local_48[1] = 0;
      local_48[2] = 0;
      local_48[3] = 0;
      local_40 = 0;
      local_38 = 0;
      iVar1 = (**(code **)(*local_30 + 0x18))(local_30,&DAT_004030f8,local_48);
      if ((iVar1 < 0) || (local_48[0] != 0xb)) {
        PropVariantClear((PROPVARIANT *)local_48);
        local_40 = local_28;
        local_38 = 0;
        local_48[0] = 0x1f;
        local_48[1] = 0;
        local_48[2] = 0;
        local_48[3] = 0;
        (**(code **)(*local_30 + 0x20))(local_30,&DAT_004030e0,local_48);
        PropVariantClear((PROPVARIANT *)local_48);
        local_38 = 0;
        local_48[0] = 0xb;
        local_48[1] = 0;
        local_48[2] = 0;
        local_48[3] = 0;
        local_40 = 1;
        (**(code **)(*local_30 + 0x20))(local_30,&DAT_004030f8,local_48);
      }
      PropVariantClear((PROPVARIANT *)local_48);
      (**(code **)(*local_30 + 0x10))();
    }
  }
LAB_0040b6ca:
  FUN_0040eea0(local_10 ^ (ulonglong)auStack_68);
  return;
}



/* === FUN_0040b6e4 @ 0040b6e4 === */

HRESULT FUN_0040b6e4(longlong param_1)

{
  HRESULT HVar1;
  longlong *local_res8;
  longlong *local_res10;
  longlong *local_res18;
  longlong *local_res20;
  longlong *local_28 [2];
  
  FUN_00408208();
  if (*(longlong *)(param_1 + 0x38) == 0) {
    local_28[0] = (longlong *)0x0;
    local_res20 = (longlong *)0x0;
    HVar1 = CoCreateInstance((IID *)&DAT_00405608,(LPUNKNOWN)0x0,0x17,(IID *)&DAT_00405618,local_28)
    ;
    if (-1 < HVar1) {
      HVar1 = (**(code **)(*local_28[0] + 0x28))
                        (local_28[0],*(undefined8 *)(param_1 + 0x48),&local_res20);
      if (-1 < HVar1) {
        local_res18 = (longlong *)0x0;
        local_res10 = (longlong *)0x0;
        local_res8 = (longlong *)0x0;
        HVar1 = (**(code **)(*local_res20 + 0x18))(local_res20,&DAT_00405628,0x17,0,&local_res18);
        if (-1 < HVar1) {
          HVar1 = (**(code **)(*local_res18 + 0x20))(local_res18,0,&local_res10);
          if (-1 < HVar1) {
            HVar1 = (**(code **)(*local_res10 + 0x40))(local_res10,&local_res8);
            if (-1 < HVar1) {
              HVar1 = (**(code **)*local_res8)(local_res8,&DAT_00405638,param_1 + 0x38);
              if (local_res8 != (longlong *)0x0) {
                (**(code **)(*local_res8 + 0x10))();
                local_res8 = (longlong *)0x0;
              }
            }
            if (local_res10 != (longlong *)0x0) {
              (**(code **)(*local_res10 + 0x10))();
              local_res10 = (longlong *)0x0;
            }
          }
          if (local_res18 != (longlong *)0x0) {
            (**(code **)(*local_res18 + 0x10))();
            local_res18 = (longlong *)0x0;
          }
        }
        (**(code **)(*local_res20 + 0x10))();
        local_res20 = (longlong *)0x0;
      }
      (**(code **)(*local_28[0] + 0x10))();
    }
  }
  else {
    HVar1 = 0;
  }
  return HVar1;
}



/* === FUN_0040b854 @ 0040b854 === */

undefined8 * FUN_0040b854(undefined8 *param_1,uint param_2)

{
  FUN_0040b890(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_0040b890 @ 0040b890 === */

void FUN_0040b890(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00405730;
  FUN_00408208();
  FUN_0040a4c0(param_1);
  return;
}



/* === FUN_0040b8c8 @ 0040b8c8 === */

undefined8 * FUN_0040b8c8(undefined8 *param_1,uint param_2)

{
  FUN_0040b904(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_0040b904 @ 0040b904 === */

void FUN_0040b904(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00405870;
  FUN_00408208();
  FUN_0040a4c0(param_1);
  return;
}



/* === FUN_0040b93c @ 0040b93c === */

undefined8 * FUN_0040b93c(undefined8 *param_1)

{
  FUN_00409e88(param_1);
  *param_1 = &PTR_FUN_00406ba0;
  FUN_00408208();
  *(undefined4 *)(param_1 + 0xb) = 0xffffffff;
  *(undefined4 *)(param_1 + 0xc) = 0xffffffff;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  *(undefined4 *)(param_1 + 10) = 0;
  *(undefined4 *)((longlong)param_1 + 0x54) = 0;
  *(undefined4 *)((longlong)param_1 + 0x5c) = 0;
  *(undefined4 *)((longlong)param_1 + 100) = 0;
  return param_1;
}



/* === FUN_0040b9a8 @ 0040b9a8 === */

undefined8 * FUN_0040b9a8(undefined8 *param_1,uint param_2)

{
  FUN_0040b9e4(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_0040b9e4 @ 0040b9e4 === */

void FUN_0040b9e4(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00406ba0;
  FUN_00408208();
  FUN_0040c124((longlong)param_1);
  FUN_00409f14(param_1);
  return;
}



/* === FUN_0040ba24 @ 0040ba24 === */

int FUN_0040ba24(longlong *param_1,longlong param_2,longlong *param_3,longlong *param_4)

{
  int iVar1;
  int iVar2;
  longlong *local_res20;
  longlong *local_98;
  longlong *local_90;
  longlong *local_88;
  longlong *local_80;
  longlong *local_78;
  undefined4 local_70 [2];
  undefined4 local_68 [2];
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  
  FUN_00408208();
  iVar1 = -0x7fffbffb;
  if ((param_4 != (longlong *)0x0) && (param_3 != (longlong *)0x0)) {
    param_1[8] = param_2;
    local_78 = (longlong *)0x0;
    FUN_00408208();
    iVar1 = (**(code **)*param_4)(param_4,&DAT_00402c50,&local_78);
    if (-1 < iVar1) {
      local_98 = (longlong *)0x0;
      FUN_00408208();
      iVar1 = (**(code **)(*param_4 + 0x20))(param_4,&LAB_00402c70,&local_98);
      if (-1 < iVar1) {
        local_90 = (longlong *)0x0;
        FUN_00408208();
        iVar1 = (**(code **)*local_98)(local_98,&DAT_00402c50,&local_90);
        if (-1 < iVar1) {
          FUN_00408208();
          iVar1 = FUN_0040a060(param_1,local_78,local_90);
          if (-1 < iVar1) {
            local_70[0] = 0;
            iVar1 = (**(code **)(*param_4 + 0x28))(param_4,local_70,param_1 + 9);
            if (-1 < iVar1) {
              param_1[7] = (longlong)param_4;
              (**(code **)(*param_4 + 8))(param_4);
              local_68[0] = 0x34;
              iVar1 = (**(code **)(*(longlong *)param_1[7] + 0x18))((longlong *)param_1[7],local_68)
              ;
              if ((-1 < iVar1) && (local_60 == 0)) {
                iVar1 = 0;
                *(undefined4 *)((longlong)param_1 + 0x54) = local_5c;
                *(undefined4 *)(param_1 + 10) = local_58;
              }
              local_88 = (longlong *)0x0;
              FUN_00408208();
              (**(code **)(*(longlong *)param_1[7] + 0x20))
                        ((longlong *)param_1[7],&DAT_00405588,param_1 + 0xd);
              FUN_00408208();
              iVar2 = (**(code **)(*(longlong *)param_1[7] + 0x20))
                                ((longlong *)param_1[7],&DAT_00406be8,&local_88);
              if (-1 < iVar2) {
                local_res20 = (longlong *)0x0;
                FUN_00408208();
                iVar2 = (**(code **)*local_88)(local_88,&DAT_00402c50,&local_res20);
                if (-1 < iVar2) {
                  (**(code **)(*param_1 + 0x18))(param_1,local_res20);
                  (**(code **)(*local_res20 + 0x10))();
                  local_res20 = (longlong *)0x0;
                }
                (**(code **)(*local_88 + 0x10))();
                local_88 = (longlong *)0x0;
              }
              FUN_00408208();
              iVar2 = (**(code **)(*(longlong *)param_1[7] + 0x20))
                                ((longlong *)param_1[7],&LAB_00406bf8,param_1 + 0xe);
              if (-1 < iVar2) {
                local_80 = (longlong *)0x0;
                FUN_00408208();
                iVar2 = (*(code *)**(undefined8 **)param_1[0xe])
                                  ((undefined8 *)param_1[0xe],&DAT_00402c50,&local_80);
                if (-1 < iVar2) {
                  iVar2 = (**(code **)(*(longlong *)param_1[0xe] + 0x30))
                                    ((longlong *)param_1[0xe],3,param_1 + 0xb);
                  if (-1 < iVar2) {
                    (**(code **)(*(longlong *)param_1[0xe] + 0x38))
                              ((longlong *)param_1[0xe],(int)param_1[0xb],(longlong)param_1 + 0x5c);
                  }
                  iVar2 = (**(code **)(*(longlong *)param_1[0xe] + 0x30))
                                    ((longlong *)param_1[0xe],0xc0,param_1 + 0xc);
                  if (-1 < iVar2) {
                    (**(code **)(*(longlong *)param_1[0xe] + 0x38))
                              ((longlong *)param_1[0xe],(int)param_1[0xc],(longlong)param_1 + 100);
                    (**(code **)(*(longlong *)param_1[0xe] + 0x20))
                              ((longlong *)param_1[0xe],(int)param_1[0xb],&local_res20);
                    (**(code **)(*(longlong *)param_1[0xe] + 0x28))
                              ((longlong *)param_1[0xe],(int)param_1[0xb],
                               (ulonglong)local_res20 & 0xffffffff);
                    (**(code **)(*(longlong *)param_1[0xe] + 0x20))
                              ((longlong *)param_1[0xe],(int)param_1[0xc],&local_res20);
                    (**(code **)(*(longlong *)param_1[0xe] + 0x28))
                              ((longlong *)param_1[0xe],(int)param_1[0xc],
                               (ulonglong)local_res20 & 0xffffffff);
                  }
                  (**(code **)(*param_1 + 0x18))(param_1,local_80);
                  (**(code **)(*local_80 + 0x10))();
                }
              }
              FUN_00408208();
              (**(code **)(*(longlong *)param_1[7] + 0x20))
                        ((longlong *)param_1[7],&DAT_00406c08,param_1 + 0xf);
            }
            param_1[6] = (longlong)param_3;
            (**(code **)(*param_3 + 8))(param_3);
            if (-1 < iVar1) {
              (**(code **)(*param_1 + 0x40))(param_1);
              (**(code **)(*local_98 + 0x30))();
            }
          }
          (**(code **)(*local_90 + 0x10))();
          local_90 = (longlong *)0x0;
        }
        (**(code **)(*local_98 + 0x10))();
        local_98 = (longlong *)0x0;
      }
      (**(code **)(*local_78 + 0x10))();
    }
  }
  return iVar1;
}



/* === FUN_0040be20 @ 0040be20 === */

void FUN_0040be20(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  int local_res8 [2];
  int local_res10 [2];
  longlong *local_res18;
  longlong *local_res20;
  
  FUN_00408208();
  if (*(longlong *)(param_1 + 0x68) != 0) {
    iVar2 = (**(code **)(**(longlong **)(param_1 + 0x68) + 0x18))
                      (*(longlong **)(param_1 + 0x68),0xe,local_res10);
    if (((-1 < iVar2) && (local_res10[0] == 1)) && (*(longlong *)(param_1 + 0x38) != 0)) {
      local_res18 = (longlong *)0x0;
      FUN_00408208();
      (**(code **)(**(longlong **)(param_1 + 0x38) + 0x20))
                (*(longlong **)(param_1 + 0x38),&LAB_00402c70,&local_res18);
      if (local_res18 != (longlong *)0x0) {
        local_res8[0] = 0;
        iVar2 = (**(code **)(*local_res18 + 0x18))(local_res18,local_res8);
        if ((-1 < iVar2) && (local_res8[0] != 0)) {
          FUN_00408208();
          local_res20 = (longlong *)0x0;
          (**(code **)**(undefined8 **)(param_1 + 0x38))
                    (*(undefined8 **)(param_1 + 0x38),&DAT_004055d8,&local_res20);
          plVar1 = local_res20;
          if (local_res20 != (longlong *)0x0) {
            FUN_00408208();
            (**(code **)(*plVar1 + 0x18))(plVar1);
            (**(code **)(*local_res20 + 0x10))();
          }
        }
        local_res8[0] = 0;
        (**(code **)(*local_res18 + 0x20))(local_res18,0);
        (**(code **)(*local_res18 + 0x10))();
      }
    }
  }
  return;
}



/* === FUN_0040bf4c @ 0040bf4c === */

void FUN_0040bf4c(longlong *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_res10 [2];
  int local_28 [4];
  
  FUN_00408208();
  if (param_2 == 0x843) {
    if ((param_3 == -0x3fffdcfe) && (FUN_00408208(), param_1[0xd] != 0)) {
      FUN_00408208();
      local_28[0] = 0;
      uVar2 = 1;
      iVar1 = (**(code **)(*(longlong *)param_1[0xd] + 0x18))((longlong *)param_1[0xd],1,local_28);
      FUN_00408208();
      if ((-1 < iVar1) && (local_28[0] != 0)) {
        local_res10[0] = 0;
        iVar1 = (**(code **)(*(longlong *)param_1[0xe] + 0x38))
                          ((longlong *)param_1[0xe],(int)param_1[0xb],local_res10);
        FUN_00408208();
        if (((-1 < iVar1) && (local_res10[0] != *(int *)((longlong)param_1 + 0x5c))) &&
           (*(int *)((longlong)param_1 + 0x5c) = local_res10[0], local_res10[0] != 0)) {
          if ((int)param_1[10] != 0x30d6) {
            uVar2 = 2;
          }
          (**(code **)(*param_1 + 0x28))(param_1,uVar2);
        }
        iVar1 = (**(code **)(*(longlong *)param_1[0xe] + 0x38))
                          ((longlong *)param_1[0xe],(int)param_1[0xc],local_res10);
        if (((-1 < iVar1) && (local_res10[0] != *(int *)((longlong)param_1 + 100))) &&
           (*(int *)((longlong)param_1 + 100) = local_res10[0], local_res10[0] != 0)) {
          (**(code **)(*param_1 + 0x28))(param_1,3);
        }
      }
    }
  }
  else {
    if (param_2 == 0x10000002) {
      if (param_3 == -0x7fffffff) {
        FUN_00408208();
        (**(code **)(*param_1 + 0x38))(param_1);
        return;
      }
      param_2 = 0x10000002;
    }
    else if (param_2 == 0x10000050) {
      (**(code **)(*param_1 + 0x40))();
      return;
    }
    FUN_00409fc0(param_1,param_2,param_3);
  }
  return;
}



/* === FUN_0040c124 @ 0040c124 === */

void FUN_0040c124(longlong param_1)

{
  int iVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  FUN_00408208();
  if ((*(longlong *)(param_1 + 0x40) != 0) && (*(longlong *)(param_1 + 0x48) != 0)) {
    FUN_00408208();
    plVar2 = (longlong *)(*(longlong *)(param_1 + 0x40) + 0x68);
    iVar1 = (**(code **)(*plVar2 + 0x30))(plVar2,*(undefined8 *)(param_1 + 0x48));
    if (iVar1 != -1) {
      plVar2 = (longlong *)(*(longlong *)(param_1 + 0x40) + 0x68);
      plVar2 = (longlong *)(**(code **)(*plVar2 + 0x38))(plVar2,iVar1);
      if (plVar2 != (longlong *)0x0) {
        plVar3 = (longlong *)(*(longlong *)(param_1 + 0x40) + 0x68);
        (**(code **)(*plVar3 + 0x20))(plVar3,*(undefined8 *)(param_1 + 0x48));
        if ((LPVOID)plVar2[1] != (LPVOID)0x0) {
          CoTaskMemFree((LPVOID)plVar2[1]);
          plVar2[1] = 0;
        }
        if (*plVar2 != 0) {
          *plVar2 = 0;
        }
        LocalFree(plVar2);
      }
    }
  }
  FUN_0040a2e0(param_1);
  if (*(LPVOID *)(param_1 + 0x48) != (LPVOID)0x0) {
    CoTaskMemFree(*(LPVOID *)(param_1 + 0x48));
    *(undefined8 *)(param_1 + 0x48) = 0;
  }
  if (*(longlong **)(param_1 + 0x38) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))();
    *(undefined8 *)(param_1 + 0x38) = 0;
  }
  if (*(longlong **)(param_1 + 0x30) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x30) + 0x10))();
    *(undefined8 *)(param_1 + 0x30) = 0;
  }
  if (*(longlong **)(param_1 + 0x68) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x68) + 0x10))();
    *(undefined8 *)(param_1 + 0x68) = 0;
  }
  if (*(longlong **)(param_1 + 0x70) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x70) + 0x10))();
    *(undefined8 *)(param_1 + 0x70) = 0;
  }
  if (*(longlong **)(param_1 + 0x78) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x78) + 0x10))();
    *(undefined8 *)(param_1 + 0x78) = 0;
  }
  return;
}



/* === FUN_0040c25c @ 0040c25c === */

void FUN_0040c25c(longlong param_1)

{
  int iVar1;
  HANDLE hObject;
  undefined8 uVar2;
  undefined4 local_res8 [2];
  longlong *local_res10;
  undefined1 local_48 [8];
  int local_40;
  uint local_3c;
  uint local_38;
  
  FUN_00408208();
  if (*(longlong *)(param_1 + 0x38) != 0) {
    (**(code **)(**(longlong **)(param_1 + 0x38) + 8))();
    FUN_00408208();
    iVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x18))
                      (*(longlong **)(param_1 + 0x38),local_48);
    if (-1 < iVar1) {
      FUN_00408208();
      if (local_40 == 0) {
        FUN_00408208();
        local_res10 = (longlong *)0x0;
        iVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x20))
                          (*(longlong **)(param_1 + 0x38),&DAT_00406be8,&local_res10);
        if (-1 < iVar1) {
          local_res8[0] = 0;
          iVar1 = (**(code **)(*local_res10 + 0x18))(local_res10,local_res8);
          FUN_00408208();
          if (-1 < iVar1) {
            FUN_00408208();
            hObject = (HANDLE)FUN_0040dcd4(local_3c,local_38);
            if (hObject != (HANDLE)0x0) {
              FUN_00408208();
              uVar2 = FUN_0040deb8(hObject);
              if (-1 < (int)uVar2) {
                FUN_00408208();
                (**(code **)(*local_res10 + 0x20))(local_res10,local_res8[0]);
              }
              if (hObject != (HANDLE)0xffffffffffffffff) {
                CloseHandle(hObject);
              }
            }
          }
          (**(code **)(*local_res10 + 0x10))();
        }
      }
    }
    (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))();
  }
  return;
}



/* === FUN_0040c420 @ 0040c420 === */

undefined8 * FUN_0040c420(undefined8 *param_1,uint param_2)

{
  FUN_0040c45c(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_0040c45c @ 0040c45c === */

void FUN_0040c45c(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00407f20;
  FUN_00408208();
  FUN_0040b9e4(param_1);
  return;
}



/* === FUN_0040c494 @ 0040c494 === */

void FUN_0040c494(longlong *param_1,int param_2,int param_3,int param_4)

{
  undefined8 uVar1;
  
  FUN_00408208();
  if (param_2 != 0x803) {
    FUN_0040bf4c(param_1,param_2,param_3);
    return;
  }
  FUN_00408208();
  if (param_3 != -0x3ffff7ff) {
    return;
  }
  if (param_4 == -0x3ebb718f) {
    FUN_00408208();
    (**(code **)(*param_1 + 0x48))(param_1);
    return;
  }
  if (param_4 == -0x3ebbce32) {
    FUN_00408208();
    (**(code **)(*param_1 + 0x50))(param_1);
    return;
  }
  if (param_4 == -0x3ebb768a) {
    FUN_00408208();
    (**(code **)(*param_1 + 0x58))(param_1);
    return;
  }
  if (param_4 == -0x3ebbb64a) {
    FUN_00408208();
    uVar1 = 1;
LAB_0040c5c0:
    (**(code **)(*param_1 + 0x60))(param_1,uVar1);
    return;
  }
  if (param_4 == -0x3ebb36ca) {
    FUN_00408208();
    uVar1 = 0;
    goto LAB_0040c5c0;
  }
  if (param_4 == -0x3ebbd62a) {
    FUN_00408208();
    uVar1 = 1;
LAB_0040c606:
    (**(code **)(*param_1 + 0x68))(param_1,uVar1);
    return;
  }
  if (param_4 == -0x3ebb56aa) {
    FUN_00408208();
    uVar1 = 0;
    goto LAB_0040c606;
  }
  if (param_4 == -0x3ebb1fe1) {
    (**(code **)(*param_1 + 0x80))(param_1);
    return;
  }
  if (param_4 == -0x3ebbef11) {
    (**(code **)(*param_1 + 0x88))(param_1);
    return;
  }
  if (param_4 == -0x3ebbaf51) {
    (**(code **)(*param_1 + 0x70))(param_1);
    return;
  }
  if (param_4 == -0x3ebb2fd1) {
    (**(code **)(*param_1 + 0x78))(param_1);
    return;
  }
  if ((param_4 == -0x3ebb619f) || (param_4 == -0x3ebb4fb1)) {
    uVar1 = 0xe;
LAB_0040c796:
    (**(code **)(*param_1 + 0x90))(param_1,uVar1);
    return;
  }
  if (param_4 == -0x3ebb5ea2) {
    uVar1 = 0xd;
    goto LAB_0040c796;
  }
  if ((param_4 == -0x3ebb01ff) || (param_4 == -0x3ebb0ff1)) {
    if (param_4 != -0x3ebb29d7) {
      (**(code **)(*param_1 + 0x90))(param_1,0xc);
    }
  }
  else if (param_4 != -0x3ebb29d7) {
    if ((param_4 == -0x3ebba15f) || (param_4 == -0x3ebb7789)) {
      if (param_4 != -0x3ebbb14f) {
        (**(code **)(*param_1 + 0x90))(param_1,0xb);
      }
    }
    else if (param_4 != -0x3ebbb14f) {
      if ((param_4 == -0x3ebb21df) || (param_4 == -0x3ebb8f71)) {
        uVar1 = 0x26;
      }
      else if ((param_4 == -0x3ebb4eb2) || (param_4 == -0x3ebbb749)) {
        uVar1 = 0x28;
      }
      else {
        if ((param_4 != -0x3ebbf709) && (param_4 != -0x3ebb7e82)) {
          if (param_4 != -0x3ebbc13f) {
            return;
          }
          (**(code **)(*param_1 + 0xa0))(param_1,0xf060);
          return;
        }
        uVar1 = 0xd;
      }
      goto LAB_0040c735;
    }
    uVar1 = 0x27;
    goto LAB_0040c735;
  }
  uVar1 = 0x25;
LAB_0040c735:
  (**(code **)(*param_1 + 0x98))(param_1,uVar1);
  return;
}



/* === FUN_0040c7c4 @ 0040c7c4 === */

void FUN_0040c7c4(longlong param_1)

{
  int iVar1;
  longlong *plVar2;
  int iVar3;
  int local_res8 [2];
  undefined4 local_res10 [2];
  longlong *local_res18;
  longlong *local_res20;
  wchar_t *local_38;
  longlong *local_30 [2];
  
  FUN_00408208();
  iVar3 = 0;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    local_res8[0] = 0;
    local_30[0] = (longlong *)0x0;
    while( true ) {
      local_res18 = (longlong *)0x0;
      iVar1 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                        (*(longlong **)(param_1 + 0x30),iVar3,2,0xf,&local_res18);
      if (iVar1 < 0) break;
      (**(code **)(*local_res18 + 0x30))(local_res18,local_30);
      if (local_30[0] != (longlong *)0x0) {
        local_res10[0] = 0;
        local_38 = (wchar_t *)0x0;
        (**(code **)(*local_30[0] + 0x28))(local_30[0],local_res10,&local_38);
        iVar1 = wcscoll(local_38,*(wchar_t **)(param_1 + 0x48));
        if (iVar1 == 0) {
          FUN_00408208();
          local_res20 = (longlong *)0x0;
          FUN_00408208();
          (**(code **)(*local_res18 + 0x28))(local_res18,&DAT_00407fc8,&local_res20);
          plVar2 = local_res20;
          if (local_res20 != (longlong *)0x0) {
            FUN_00408208();
            if (iVar3 == 0) {
              (**(code **)(*plVar2 + 0x48))(plVar2,local_res8);
              FUN_00408208();
              plVar2 = local_res20;
            }
            if (local_res8[0] == 0) {
              FUN_00408208();
              (**(code **)(*plVar2 + 0x38))(plVar2);
            }
            else {
              FUN_00408208();
              (**(code **)(*plVar2 + 0x40))(plVar2);
            }
            FUN_00408208();
            (**(code **)(*local_res20 + 0x10))();
          }
        }
        FUN_00408208();
        CoTaskMemFree(local_38);
        local_38 = (wchar_t *)0x0;
        (**(code **)(*local_30[0] + 0x10))();
        local_30[0] = (longlong *)0x0;
      }
      FUN_00408208();
      (**(code **)(*local_res18 + 0x10))();
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



/* === FUN_0040c9fc @ 0040c9fc === */

void FUN_0040c9fc(longlong param_1)

{
  int iVar1;
  longlong *plVar2;
  int iVar3;
  int local_res8 [2];
  undefined4 local_res10 [2];
  longlong *local_res18;
  longlong *local_res20;
  wchar_t *local_38;
  longlong *local_30 [2];
  
  FUN_00408208();
  iVar3 = 0;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    local_res8[0] = 0;
    local_30[0] = (longlong *)0x0;
    while( true ) {
      local_res18 = (longlong *)0x0;
      iVar1 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                        (*(longlong **)(param_1 + 0x30),iVar3,2,0xf,&local_res18);
      if (iVar1 < 0) break;
      (**(code **)(*local_res18 + 0x30))(local_res18,local_30);
      if (local_30[0] != (longlong *)0x0) {
        local_res10[0] = 0;
        local_38 = (wchar_t *)0x0;
        (**(code **)(*local_30[0] + 0x28))(local_30[0],local_res10,&local_38);
        iVar1 = wcscoll(local_38,*(wchar_t **)(param_1 + 0x48));
        if (iVar1 == 0) {
          FUN_00408208();
          local_res20 = (longlong *)0x0;
          FUN_00408208();
          (**(code **)(*local_res18 + 0x28))(local_res18,&DAT_00407fd8,&local_res20);
          plVar2 = local_res20;
          if (local_res20 != (longlong *)0x0) {
            FUN_00408208();
            if (iVar3 == 0) {
              (**(code **)(*plVar2 + 0x40))(plVar2,local_res8);
              FUN_00408208();
              plVar2 = local_res20;
            }
            if (local_res8[0] == 0) {
              FUN_00408208();
              (**(code **)(*plVar2 + 0x30))(plVar2);
            }
            else {
              FUN_00408208();
              (**(code **)(*plVar2 + 0x38))(plVar2);
            }
            FUN_00408208();
            (**(code **)(*local_res20 + 0x10))();
          }
        }
        FUN_00408208();
        CoTaskMemFree(local_38);
        local_38 = (wchar_t *)0x0;
        (**(code **)(*local_30[0] + 0x10))();
        local_30[0] = (longlong *)0x0;
      }
      FUN_00408208();
      (**(code **)(*local_res18 + 0x10))();
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



/* === FUN_0040cc34 @ 0040cc34 === */

void FUN_0040cc34(longlong param_1)

{
  int iVar1;
  longlong *plVar2;
  int iVar3;
  int local_res8 [2];
  undefined4 local_res10 [2];
  longlong *local_res18;
  longlong *local_res20;
  wchar_t *local_38;
  longlong *local_30 [2];
  
  FUN_00408208();
  iVar3 = 0;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    local_res8[0] = 0;
    local_30[0] = (longlong *)0x0;
    while( true ) {
      local_res18 = (longlong *)0x0;
      iVar1 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                        (*(longlong **)(param_1 + 0x30),iVar3,2,0xf,&local_res18);
      if (iVar1 < 0) break;
      (**(code **)(*local_res18 + 0x30))(local_res18,local_30);
      if (local_30[0] != (longlong *)0x0) {
        local_res10[0] = 0;
        local_38 = (wchar_t *)0x0;
        (**(code **)(*local_30[0] + 0x28))(local_30[0],local_res10,&local_38);
        iVar1 = wcscoll(local_38,*(wchar_t **)(param_1 + 0x48));
        if (iVar1 == 0) {
          FUN_00408208();
          local_res20 = (longlong *)0x0;
          FUN_00408208();
          (**(code **)(*local_res18 + 0x28))(local_res18,&DAT_00407fe8,&local_res20);
          plVar2 = local_res20;
          if (local_res20 != (longlong *)0x0) {
            FUN_00408208();
            if (iVar3 == 0) {
              (**(code **)(*plVar2 + 0x28))(plVar2,local_res8);
              FUN_00408208();
              plVar2 = local_res20;
            }
            if (local_res8[0] == 0) {
              FUN_00408208();
              (**(code **)(*plVar2 + 0x18))(plVar2);
            }
            else {
              FUN_00408208();
              (**(code **)(*plVar2 + 0x20))(plVar2);
            }
            FUN_00408208();
            (**(code **)(*local_res20 + 0x10))();
          }
        }
        FUN_00408208();
        CoTaskMemFree(local_38);
        local_38 = (wchar_t *)0x0;
        (**(code **)(*local_30[0] + 0x10))();
        local_30[0] = (longlong *)0x0;
      }
      FUN_00408208();
      (**(code **)(*local_res18 + 0x10))();
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



/* === FUN_0040ce6c @ 0040ce6c === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040ce6c(longlong param_1,int param_2)

{
  float fVar1;
  longlong *plVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float local_res8 [2];
  float local_res18 [2];
  float local_res20 [2];
  undefined4 local_58;
  undefined1 local_54 [4];
  undefined1 local_50 [8];
  longlong *local_48;
  longlong *local_40;
  wchar_t *local_38;
  longlong *local_30 [3];
  
  FUN_00408208();
  if (*(longlong *)(param_1 + 0x30) != 0) {
    iVar4 = 0;
    local_40 = (longlong *)0x0;
    local_30[0] = (longlong *)0x0;
    iVar3 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                      (*(longlong **)(param_1 + 0x30),0,2,0xf,&local_40);
    fVar1 = DAT_0040818c;
    while (-1 < iVar3) {
      (**(code **)(*local_40 + 0x30))(local_40,local_30);
      if (local_30[0] != (longlong *)0x0) {
        local_58 = 0;
        local_38 = (wchar_t *)0x0;
        (**(code **)(*local_30[0] + 0x28))(local_30[0],&local_58,&local_38);
        iVar3 = wcscoll(local_38,*(wchar_t **)(param_1 + 0x48));
        if (iVar3 == 0) {
          FUN_00408208();
          local_48 = (longlong *)0x0;
          FUN_00408208();
          (**(code **)(*local_40 + 0x28))(local_40,&DAT_00407fe8,&local_48);
          plVar2 = local_48;
          if (local_48 != (longlong *)0x0) {
            FUN_00408208();
            FUN_00408208();
            (**(code **)(*plVar2 + 0x18))(plVar2);
            iVar3 = (**(code **)(*local_48 + 0x30))
                              (local_48,local_res20,local_res18,local_50,local_54);
            if ((-1 < iVar3) &&
               (iVar3 = (**(code **)(*local_48 + 0x38))(local_48,local_res8), -1 < iVar3)) {
              if (param_2 == 1) {
                local_res8[0] = local_res8[0] + _DAT_00408190;
                if (((int)(local_res8[0] * fVar1) < (int)(local_res20[0] * fVar1)) ||
                   (fVar5 = local_res8[0],
                   (int)(local_res18[0] * fVar1) < (int)(local_res8[0] * fVar1))) {
                  fVar5 = local_res18[0];
                }
              }
              else {
                local_res8[0] = local_res8[0] + (0.0 - _DAT_00408190);
                if (((int)(local_res8[0] * fVar1) < (int)(local_res20[0] * fVar1)) ||
                   (fVar5 = local_res8[0],
                   (int)(local_res18[0] * fVar1) < (int)(local_res8[0] * fVar1))) {
                  fVar5 = local_res20[0];
                }
              }
              (**(code **)(*local_48 + 0x40))(local_48,fVar5);
            }
            FUN_00408208();
            (**(code **)(*local_48 + 0x10))();
          }
        }
        FUN_00408208();
        CoTaskMemFree(local_38);
        local_38 = (wchar_t *)0x0;
        (**(code **)(*local_30[0] + 0x10))();
        local_30[0] = (longlong *)0x0;
      }
      FUN_00408208();
      (**(code **)(*local_40 + 0x10))();
      local_40 = (longlong *)0x0;
      iVar4 = iVar4 + 1;
      iVar3 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                        (*(longlong **)(param_1 + 0x30),iVar4,2,0xf,&local_40);
    }
  }
  return;
}



/* === FUN_0040d15c @ 0040d15c === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040d15c(longlong param_1,int param_2)

{
  float fVar1;
  longlong *plVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float local_res8 [4];
  float local_res18 [2];
  float local_res20 [2];
  longlong *local_78;
  undefined4 local_70;
  int local_6c;
  longlong *local_68;
  longlong *local_60;
  longlong *local_58;
  wchar_t *local_50;
  undefined4 local_48;
  undefined1 local_44 [4];
  undefined1 local_40 [24];
  
  FUN_00408208();
  iVar4 = 0;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    local_78 = (longlong *)0x0;
    local_58 = (longlong *)0x0;
    iVar3 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                      (*(longlong **)(param_1 + 0x30),0,2,0xf,&local_78);
    fVar1 = DAT_0040818c;
    while (-1 < iVar3) {
      (**(code **)(*local_78 + 0x30))(local_78,&local_58);
      if (local_58 != (longlong *)0x0) {
        local_48 = 0;
        local_50 = (wchar_t *)0x0;
        (**(code **)(*local_58 + 0x28))(local_58,&local_48,&local_50);
        iVar3 = wcscoll(local_50,*(wchar_t **)(param_1 + 0x48));
        if (iVar3 == 0) {
          FUN_00408208();
          local_60 = (longlong *)0x0;
          local_70 = 0;
          local_6c = 0;
          local_68 = (longlong *)0x0;
          FUN_00408208();
          (**(code **)(*local_78 + 0x28))(local_78,&DAT_00407fc8,&local_60);
          plVar2 = local_60;
          if (local_60 != (longlong *)0x0) {
            FUN_00408208();
            FUN_00408208();
            (**(code **)(*plVar2 + 0x38))(plVar2);
            iVar3 = (**(code **)(*local_60 + 0x20))(local_60,&local_70);
            if ((-1 < iVar3) &&
               (iVar3 = (**(code **)(*local_60 + 0x18))(local_60,local_70,&local_68), -1 < iVar3)) {
              iVar3 = (**(code **)(*local_68 + 0x18))(local_68,&local_6c);
              plVar2 = local_68;
              if ((-1 < iVar3) &&
                 (((local_6c == 6 &&
                   (iVar3 = (**(code **)(*local_68 + 0x20))
                                      (local_68,local_res20,local_res18,local_44,local_40),
                   -1 < iVar3)) &&
                  (iVar3 = (**(code **)(*plVar2 + 0x28))(plVar2,local_res8), -1 < iVar3)))) {
                if (param_2 == 1) {
                  local_res8[0] = local_res8[0] + _DAT_00408188;
                  if (((int)(local_res8[0] * fVar1) < (int)(local_res20[0] * fVar1)) ||
                     (fVar5 = local_res8[0],
                     (int)(local_res18[0] * fVar1) < (int)(local_res8[0] * fVar1))) {
                    fVar5 = local_res18[0];
                  }
                }
                else {
                  local_res8[0] = local_res8[0] + (0.0 - _DAT_00408188);
                  if (((int)(local_res8[0] * fVar1) < (int)(local_res20[0] * fVar1)) ||
                     (fVar5 = local_res8[0],
                     (int)(local_res18[0] * fVar1) < (int)(local_res8[0] * fVar1))) {
                    fVar5 = local_res20[0];
                  }
                }
                (**(code **)(*plVar2 + 0x30))(plVar2,fVar5);
              }
              (**(code **)(*local_68 + 0x10))();
              local_68 = (longlong *)0x0;
            }
            FUN_00408208();
            (**(code **)(*local_60 + 0x10))();
          }
        }
        FUN_00408208();
        CoTaskMemFree(local_50);
        local_50 = (wchar_t *)0x0;
        (**(code **)(*local_58 + 0x10))();
        local_58 = (longlong *)0x0;
      }
      FUN_00408208();
      (**(code **)(*local_78 + 0x10))();
      local_78 = (longlong *)0x0;
      iVar4 = iVar4 + 1;
      iVar3 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                        (*(longlong **)(param_1 + 0x30),iVar4,2,0xf,&local_78);
    }
  }
  return;
}



/* === FUN_0040d4c8 @ 0040d4c8 === */

void FUN_0040d4c8(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  int iVar3;
  undefined4 local_res8 [2];
  longlong *local_res10;
  wchar_t *local_res18;
  longlong *local_res20;
  longlong *local_28 [2];
  
  FUN_00408208();
  if (*(longlong *)(param_1 + 0x30) != 0) {
    iVar3 = 0;
    local_res20 = (longlong *)0x0;
    while( true ) {
      local_res10 = (longlong *)0x0;
      iVar2 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                        (*(longlong **)(param_1 + 0x30),iVar3,2,0xf,&local_res10);
      if (iVar2 < 0) break;
      (**(code **)(*local_res10 + 0x30))(local_res10,&local_res20);
      if (local_res20 != (longlong *)0x0) {
        local_res8[0] = 0;
        local_res18 = (wchar_t *)0x0;
        (**(code **)(*local_res20 + 0x28))(local_res20,local_res8,&local_res18);
        iVar2 = wcscoll(local_res18,*(wchar_t **)(param_1 + 0x48));
        if (iVar2 == 0) {
          FUN_00408208();
          local_28[0] = (longlong *)0x0;
          FUN_00408208();
          (**(code **)(*local_res10 + 0x28))(local_res10,&DAT_00407fc8,local_28);
          plVar1 = local_28[0];
          if (local_28[0] != (longlong *)0x0) {
            FUN_00408208();
            FUN_00408208();
            (**(code **)(*plVar1 + 0x38))(plVar1);
            FUN_00408208();
            (**(code **)(*local_28[0] + 0x10))();
          }
        }
        FUN_00408208();
        CoTaskMemFree(local_res18);
        local_res18 = (wchar_t *)0x0;
        (**(code **)(*local_res20 + 0x10))();
        local_res20 = (longlong *)0x0;
      }
      FUN_00408208();
      (**(code **)(*local_res10 + 0x10))();
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



/* === FUN_0040d680 @ 0040d680 === */

void FUN_0040d680(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  int iVar3;
  undefined4 local_res8 [2];
  longlong *local_res10;
  wchar_t *local_res18;
  longlong *local_res20;
  longlong *local_28 [2];
  
  FUN_00408208();
  if (*(longlong *)(param_1 + 0x30) != 0) {
    iVar3 = 0;
    local_res20 = (longlong *)0x0;
    while( true ) {
      local_res10 = (longlong *)0x0;
      iVar2 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                        (*(longlong **)(param_1 + 0x30),iVar3,2,0xf,&local_res10);
      if (iVar2 < 0) break;
      (**(code **)(*local_res10 + 0x30))(local_res10,&local_res20);
      if (local_res20 != (longlong *)0x0) {
        local_res8[0] = 0;
        local_res18 = (wchar_t *)0x0;
        (**(code **)(*local_res20 + 0x28))(local_res20,local_res8,&local_res18);
        iVar2 = wcscoll(local_res18,*(wchar_t **)(param_1 + 0x48));
        if (iVar2 == 0) {
          FUN_00408208();
          local_28[0] = (longlong *)0x0;
          FUN_00408208();
          (**(code **)(*local_res10 + 0x28))(local_res10,&DAT_00407fc8,local_28);
          plVar1 = local_28[0];
          if (local_28[0] != (longlong *)0x0) {
            FUN_00408208();
            FUN_00408208();
            (**(code **)(*plVar1 + 0x40))(plVar1);
            FUN_00408208();
            (**(code **)(*local_28[0] + 0x10))();
          }
        }
        FUN_00408208();
        CoTaskMemFree(local_res18);
        local_res18 = (wchar_t *)0x0;
        (**(code **)(*local_res20 + 0x10))();
        local_res20 = (longlong *)0x0;
      }
      FUN_00408208();
      (**(code **)(*local_res10 + 0x10))();
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



/* === FUN_0040d838 @ 0040d838 === */

void FUN_0040d838(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  int iVar3;
  undefined4 local_res8 [2];
  longlong *local_res10;
  wchar_t *local_res18;
  longlong *local_res20;
  longlong *local_28 [2];
  
  FUN_00408208();
  if (*(longlong *)(param_1 + 0x30) != 0) {
    iVar3 = 0;
    local_res20 = (longlong *)0x0;
    while( true ) {
      local_res10 = (longlong *)0x0;
      iVar2 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                        (*(longlong **)(param_1 + 0x30),iVar3,2,0xf,&local_res10);
      if (iVar2 < 0) break;
      (**(code **)(*local_res10 + 0x30))(local_res10,&local_res20);
      if (local_res20 != (longlong *)0x0) {
        local_res8[0] = 0;
        local_res18 = (wchar_t *)0x0;
        (**(code **)(*local_res20 + 0x28))(local_res20,local_res8,&local_res18);
        iVar2 = wcscoll(local_res18,*(wchar_t **)(param_1 + 0x48));
        if (iVar2 == 0) {
          FUN_00408208();
          local_28[0] = (longlong *)0x0;
          FUN_00408208();
          (**(code **)(*local_res10 + 0x28))(local_res10,&DAT_00407fe8,local_28);
          plVar1 = local_28[0];
          if (local_28[0] != (longlong *)0x0) {
            FUN_00408208();
            FUN_00408208();
            (**(code **)(*plVar1 + 0x18))(plVar1);
            FUN_00408208();
            (**(code **)(*local_28[0] + 0x10))();
          }
        }
        FUN_00408208();
        CoTaskMemFree(local_res18);
        local_res18 = (wchar_t *)0x0;
        (**(code **)(*local_res20 + 0x10))();
        local_res20 = (longlong *)0x0;
      }
      FUN_00408208();
      (**(code **)(*local_res10 + 0x10))();
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



/* === FUN_0040d9f0 @ 0040d9f0 === */

void FUN_0040d9f0(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  int iVar3;
  undefined4 local_res8 [2];
  longlong *local_res10;
  wchar_t *local_res18;
  longlong *local_res20;
  longlong *local_28 [2];
  
  FUN_00408208();
  if (*(longlong *)(param_1 + 0x30) != 0) {
    iVar3 = 0;
    local_res20 = (longlong *)0x0;
    while( true ) {
      local_res10 = (longlong *)0x0;
      iVar2 = (**(code **)(**(longlong **)(param_1 + 0x30) + 0x18))
                        (*(longlong **)(param_1 + 0x30),iVar3,2,0xf,&local_res10);
      if (iVar2 < 0) break;
      (**(code **)(*local_res10 + 0x30))(local_res10,&local_res20);
      if (local_res20 != (longlong *)0x0) {
        local_res8[0] = 0;
        local_res18 = (wchar_t *)0x0;
        (**(code **)(*local_res20 + 0x28))(local_res20,local_res8,&local_res18);
        iVar2 = wcscoll(local_res18,*(wchar_t **)(param_1 + 0x48));
        if (iVar2 == 0) {
          FUN_00408208();
          local_28[0] = (longlong *)0x0;
          FUN_00408208();
          (**(code **)(*local_res10 + 0x28))(local_res10,&DAT_00407fe8,local_28);
          plVar1 = local_28[0];
          if (local_28[0] != (longlong *)0x0) {
            FUN_00408208();
            FUN_00408208();
            (**(code **)(*plVar1 + 0x20))(plVar1);
            FUN_00408208();
            (**(code **)(*local_28[0] + 0x10))();
          }
        }
        FUN_00408208();
        CoTaskMemFree(local_res18);
        local_res18 = (wchar_t *)0x0;
        (**(code **)(*local_res20 + 0x10))();
        local_res20 = (longlong *)0x0;
      }
      FUN_00408208();
      (**(code **)(*local_res10 + 0x10))();
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



/* === FUN_0040dba8 @ 0040dba8 === */

void FUN_0040dba8(undefined8 param_1,int param_2)

{
  HWND pHVar1;
  HWND pHVar2;
  
  pHVar1 = GetForegroundWindow();
  pHVar2 = GetDesktopWindow();
                    /* WARNING: Could not recover jumptable at 0x0040dbde. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  PostMessageW(pHVar1,0x319,pHVar2,param_2 << 0x10);
  return;
}



/* === FUN_0040dbec @ 0040dbec === */

void FUN_0040dbec(undefined8 param_1,BYTE param_2)

{
  keybd_event(param_2,'\0',1,0);
  Sleep(0x80);
                    /* WARNING: Could not recover jumptable at 0x0040dc20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  keybd_event(param_2,'\0',3,0);
  return;
}



/* === FUN_0040dc30 @ 0040dc30 === */

void FUN_0040dc30(undefined8 param_1,undefined4 param_2)

{
  HWND pHVar1;
  
  pHVar1 = GetForegroundWindow();
                    /* WARNING: Could not recover jumptable at 0x0040dc51. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  PostMessageW(pHVar1,0x112,param_2,0);
  return;
}



/* === FUN_0040dc60 @ 0040dc60 === */

undefined8 * FUN_0040dc60(undefined8 *param_1,uint param_2)

{
  FUN_0040dc9c(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_0040dc9c @ 0040dc9c === */

void FUN_0040dc9c(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_004080e0;
  FUN_00408208();
  FUN_0040b9e4(param_1);
  return;
}



/* === FUN_0040dcd4 @ 0040dcd4 === */

void FUN_0040dcd4(uint param_1,uint param_2)

{
  char cVar1;
  BOOL BVar2;
  DWORD DVar3;
  HDEVINFO DeviceInfoSet;
  PSP_DEVICE_INTERFACE_DETAIL_DATA_W DeviceInterfaceDetailData;
  HANDLE pvVar4;
  DWORD MemberIndex;
  bool bVar5;
  undefined1 auStackY_a8 [32];
  DWORD local_68 [2];
  undefined4 local_60;
  ushort local_5c;
  ushort local_5a;
  GUID local_50;
  _SP_DEVICE_INTERFACE_DATA local_40;
  ulonglong local_20;
  
  local_20 = DAT_00410108 ^ (ulonglong)auStackY_a8;
  DeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)0x0;
  local_68[0] = 0;
  MemberIndex = 0;
  HidD_GetHidGuid(&local_50);
  DeviceInfoSet = SetupDiGetClassDevsW(&local_50,(PCWSTR)0x0,(HWND)0x0,0x12);
  if (DeviceInfoSet != (HDEVINFO)0x0) {
    do {
      local_40.cbSize = 0x20;
      BVar2 = SetupDiEnumDeviceInterfaces
                        (DeviceInfoSet,(PSP_DEVINFO_DATA)0x0,&local_50,MemberIndex,&local_40);
      if (BVar2 == 0) {
        DVar3 = GetLastError();
        bVar5 = DVar3 == 0x103;
LAB_0040de5a:
        if (bVar5) goto LAB_0040de64;
      }
      else {
        SetupDiGetDeviceInterfaceDetailW
                  (DeviceInfoSet,&local_40,(PSP_DEVICE_INTERFACE_DETAIL_DATA_W)0x0,0,local_68,
                   (PSP_DEVINFO_DATA)0x0);
        if (local_68[0] != 0) {
          if (DeviceInterfaceDetailData != (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)0x0) {
            free(DeviceInterfaceDetailData);
          }
          DeviceInterfaceDetailData = malloc((ulonglong)local_68[0]);
          if (DeviceInterfaceDetailData != (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)0x0) {
            DeviceInterfaceDetailData->cbSize = 8;
            BVar2 = SetupDiGetDeviceInterfaceDetailW
                              (DeviceInfoSet,&local_40,DeviceInterfaceDetailData,local_68[0],
                               local_68,(PSP_DEVINFO_DATA)0x0);
            if (BVar2 != 0) {
              pvVar4 = CreateFileW(DeviceInterfaceDetailData->DevicePath,0xc0000000,3,
                                   (LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
              if (pvVar4 != (HANDLE)0xffffffffffffffff) {
                local_60 = 0xc;
                cVar1 = HidD_GetAttributes(pvVar4);
                if ((cVar1 != '\0') && (local_5c == param_1)) {
                  bVar5 = local_5a == param_2;
                  goto LAB_0040de5a;
                }
              }
            }
          }
        }
      }
      MemberIndex = MemberIndex + 1;
    } while( true );
  }
LAB_0040de81:
  FUN_0040eea0(local_20 ^ (ulonglong)auStackY_a8);
  return;
LAB_0040de64:
  if (DeviceInterfaceDetailData != (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)0x0) {
    free(DeviceInterfaceDetailData);
  }
  if (DeviceInfoSet != (HDEVINFO)0xffffffffffffffff) {
    SetupDiDestroyDeviceInfoList(DeviceInfoSet);
  }
  goto LAB_0040de81;
}



/* === FUN_0040deb8 @ 0040deb8 === */

undefined8 FUN_0040deb8(HANDLE param_1)

{
  char cVar1;
  int iVar2;
  BOOL BVar3;
  undefined4 local_res8 [8];
  undefined4 in_stack_00000030;
  undefined8 in_stack_ffffffffffffffc8;
  undefined4 uVar4;
  DWORD local_18 [2];
  undefined8 local_10;
  
  uVar4 = (undefined4)((ulonglong)in_stack_ffffffffffffffc8 >> 0x20);
  local_10 = 0;
  if (param_1 != (HANDLE)0xffffffffffffffff) {
    cVar1 = HidD_GetPreparsedData(param_1,&local_10);
    if (cVar1 != '\0') {
      local_res8[0] = 0;
      local_18[0] = 0;
      iVar2 = HidP_SetUsageValue(1,0xc,0,0,CONCAT44(uVar4,in_stack_00000030),local_10,local_res8,4);
      if ((-1 < iVar2) &&
         (BVar3 = WriteFile(param_1,local_res8,4,local_18,(LPOVERLAPPED)0x0), BVar3 != 0)) {
        HidD_FreePreparsedData(local_10);
        return 0;
      }
      HidD_FreePreparsedData(local_10);
    }
  }
  return 0x80004005;
}



/* === FUN_0040df78 @ 0040df78 === */

ulonglong FUN_0040df78(undefined8 param_1,short *param_2,undefined8 param_3)

{
  uint uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  longlong *local_res20;
  longlong *local_18 [2];
  
  local_18[0] = (longlong *)0x0;
  local_res20 = (longlong *)0x0;
  uVar1 = CoCreateInstance((IID *)&DAT_004012a8,(LPUNKNOWN)0x0,1,(IID *)&DAT_00408128,local_18);
  uVar4 = (ulonglong)uVar1;
  if ((int)uVar1 < 0) {
    uVar1 = CoCreateInstance((IID *)&DAT_004012a8,(LPUNKNOWN)0x0,1,(IID *)&DAT_00408138,&local_res20
                            );
    uVar4 = (ulonglong)uVar1;
    if ((int)uVar1 < 0) {
      return uVar4;
    }
  }
  plVar2 = LocalAlloc(0x40,0x28);
  if (plVar2 == (longlong *)0x0) {
    plVar2 = (longlong *)0x0;
  }
  else {
    plVar2[1] = 0;
    plVar2[2] = 0;
    plVar2[3] = 0;
    *(undefined4 *)((longlong)plVar2 + 0x24) = 0;
    *plVar2 = (longlong)&PTR_FUN_00408158;
  }
  if (plVar2 != (longlong *)0x0) {
    (**(code **)(*plVar2 + 8))(plVar2);
    uVar3 = FUN_0040e59c((longlong)plVar2,param_2,local_18[0],local_res20);
    uVar4 = uVar3 & 0xffffffff;
    if (-1 < (int)uVar3) {
      uVar1 = (**(code **)*plVar2)(plVar2,&DAT_00408148,param_3);
      uVar4 = (ulonglong)uVar1;
    }
    (**(code **)(*plVar2 + 0x10))(plVar2);
  }
  if (local_res20 != (longlong *)0x0) {
    (**(code **)(*local_res20 + 0x10))();
    local_res20 = (longlong *)0x0;
  }
  if (local_18[0] != (longlong *)0x0) {
    (**(code **)(*local_18[0] + 0x10))();
  }
  return uVar4;
}



/* === FUN_0040e0bc @ 0040e0bc === */

int FUN_0040e0bc(undefined8 param_1,undefined4 *param_2)

{
  HRESULT HVar1;
  int iVar2;
  longlong *plVar3;
  LPVOID local_res18;
  longlong *local_res20;
  longlong *local_18 [2];
  
  local_18[0] = (longlong *)0x0;
  local_res20 = (longlong *)0x0;
  HVar1 = CoCreateInstance((IID *)&DAT_004012a8,(LPUNKNOWN)0x0,1,(IID *)&DAT_00408128,local_18);
  if ((HVar1 < 0) &&
     (HVar1 = CoCreateInstance((IID *)&DAT_004012a8,(LPUNKNOWN)0x0,1,(IID *)&DAT_00408138,
                               &local_res20), HVar1 < 0)) {
    return HVar1;
  }
  local_res18 = (LPVOID)0x0;
  plVar3 = local_18[0];
  if (local_18[0] == (longlong *)0x0) {
    plVar3 = local_res20;
  }
  iVar2 = (**(code **)(*plVar3 + 0x20))(plVar3,param_1,0,&local_res18);
  if (-1 < iVar2) {
    *param_2 = *(undefined4 *)((longlong)local_res18 + 0x14);
    CoTaskMemFree(local_res18);
    local_res18 = (LPVOID)0x0;
  }
  if (local_res20 != (longlong *)0x0) {
    (**(code **)(*local_res20 + 0x10))();
    local_res20 = (longlong *)0x0;
  }
  if (local_18[0] != (longlong *)0x0) {
    (**(code **)(*local_18[0] + 0x10))();
  }
  return iVar2;
}



/* === FUN_0040e1b0 @ 0040e1b0 === */

HRESULT FUN_0040e1b0(undefined8 param_1,undefined4 param_2,ushort param_3)

{
  HRESULT HVar1;
  int iVar2;
  uint uVar3;
  longlong *plVar4;
  LPVOID local_res20;
  longlong *local_18;
  longlong *local_10;
  
  local_10 = (longlong *)0x0;
  local_18 = (longlong *)0x0;
  HVar1 = CoCreateInstance((IID *)&DAT_004012a8,(LPUNKNOWN)0x0,1,(IID *)&DAT_00408128,&local_10);
  if ((-1 < HVar1) ||
     (HVar1 = CoCreateInstance((IID *)&DAT_004012a8,(LPUNKNOWN)0x0,1,(IID *)&DAT_00408138,&local_18)
     , -1 < HVar1)) {
    local_res20 = (LPVOID)0x0;
    plVar4 = local_10;
    if (local_10 == (longlong *)0x0) {
      plVar4 = local_18;
    }
    HVar1 = (**(code **)(*plVar4 + 0x20))(plVar4,param_1,0,&local_res20);
    if (-1 < HVar1) {
      *(undefined4 *)((longlong)local_res20 + 4) = param_2;
      *(ushort *)((longlong)local_res20 + 0x12) = param_3;
      *(ushort *)((longlong)local_res20 + 0xe) = param_3;
      iVar2 = (uint)param_3 * (uint)*(ushort *)((longlong)local_res20 + 2);
      uVar3 = (int)(iVar2 + (iVar2 >> 0x1f & 7U)) >> 3;
      *(short *)((longlong)local_res20 + 0xc) = (short)uVar3;
      *(uint *)((longlong)local_res20 + 8) = (uVar3 & 0xffff) * *(int *)((longlong)local_res20 + 4);
      if (local_10 == (longlong *)0x0) {
        HVar1 = (**(code **)(*local_18 + 0x30))(local_18,param_1,local_res20,0);
      }
      else {
        HVar1 = (**(code **)(*local_10 + 0x28))();
      }
      if ((HVar1 < 0) &&
         ((*(short *)((longlong)local_res20 + 0x12) == 8 ||
          (*(short *)((longlong)local_res20 + 0x12) == 0x18)))) {
        if (*(short *)((longlong)local_res20 + 0x12) == 8) {
          *(undefined2 *)((longlong)local_res20 + 0xe) = 0x10;
        }
        else if (*(short *)((longlong)local_res20 + 0x12) == 0x18) {
          *(undefined2 *)((longlong)local_res20 + 0xe) = 0x20;
        }
        iVar2 = (uint)*(ushort *)((longlong)local_res20 + 0xe) *
                (uint)*(ushort *)((longlong)local_res20 + 2);
        uVar3 = (int)(iVar2 + (iVar2 >> 0x1f & 7U)) >> 3;
        *(short *)((longlong)local_res20 + 0xc) = (short)uVar3;
        *(uint *)((longlong)local_res20 + 8) =
             (uVar3 & 0xffff) * *(int *)((longlong)local_res20 + 4);
        if (local_10 == (longlong *)0x0) {
          HVar1 = (**(code **)(*local_18 + 0x30))(local_18,param_1,local_res20,0);
        }
        else {
          HVar1 = (**(code **)(*local_10 + 0x28))();
        }
      }
      CoTaskMemFree(local_res20);
      local_res20 = (LPVOID)0x0;
    }
    if (local_18 != (longlong *)0x0) {
      (**(code **)(*local_18 + 0x10))();
      local_18 = (longlong *)0x0;
    }
    if (local_10 != (longlong *)0x0) {
      (**(code **)(*local_10 + 0x10))();
    }
  }
  return HVar1;
}



/* === FUN_0040e3bc @ 0040e3bc === */

undefined8 * FUN_0040e3bc(undefined8 *param_1,uint param_2)

{
  FUN_0040e3f8(param_1);
  if (((param_2 & 1) != 0) && (param_1 != (undefined8 *)0x0)) {
    LocalFree(param_1);
  }
  return param_1;
}



/* === FUN_0040e3f8 @ 0040e3f8 === */

void FUN_0040e3f8(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_00408158;
  if ((longlong *)param_1[3] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[3] + 0x10))();
    param_1[3] = 0;
  }
  if ((longlong *)param_1[2] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[2] + 0x10))();
    param_1[2] = 0;
  }
  if ((HLOCAL)param_1[1] != (HLOCAL)0x0) {
    LocalFree((HLOCAL)param_1[1]);
    param_1[1] = 0;
  }
  return;
}



/* === FUN_0040e454 @ 0040e454 === */

undefined8 FUN_0040e454(longlong *param_1,ulonglong *param_2,undefined8 *param_3)

{
  int iVar1;
  bool bVar2;
  
  *param_3 = 0;
  bVar2 = *param_2 < DAT_00403498;
  if ((*param_2 == DAT_00403498) && (bVar2 = param_2[1] < DAT_004034a0, param_2[1] == DAT_004034a0))
  {
    iVar1 = 0;
  }
  else {
    iVar1 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
  }
  if (iVar1 != 0) {
    bVar2 = *param_2 < DAT_00408148;
    if ((*param_2 == DAT_00408148) &&
       (bVar2 = param_2[1] < DAT_00408150, param_2[1] == DAT_00408150)) {
      iVar1 = 0;
    }
    else {
      iVar1 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
    }
    if (iVar1 != 0) goto LAB_0040e4c1;
  }
  *param_3 = param_1;
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 8))();
    return 0;
  }
LAB_0040e4c1:
  *param_3 = 0;
  return 0x80004002;
}



/* === FUN_0040e4d8 @ 0040e4d8 === */

int FUN_0040e4d8(longlong param_1)

{
  int *piVar1;
  int iVar2;
  
  LOCK();
  piVar1 = (int *)(param_1 + 0x24);
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + 1;
  UNLOCK();
  return iVar2 + 1;
}



/* === FUN_0040e4ec @ 0040e4ec === */

int FUN_0040e4ec(longlong *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  LOCK();
  piVar1 = (int *)((longlong)param_1 + 0x24);
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  iVar3 = iVar2 + -1;
  if ((iVar3 == 0) && (param_1 != (longlong *)0x0)) {
    (**(code **)(*param_1 + 0x28))(param_1,iVar2);
  }
  return iVar3;
}



/* === FUN_0040e51c @ 0040e51c === */

void FUN_0040e51c(longlong param_1,undefined8 param_2,undefined8 param_3)

{
  if (*(longlong *)(param_1 + 0x10) == 0) {
    (**(code **)(**(longlong **)(param_1 + 0x18) + 0x58))
              (*(longlong **)(param_1 + 0x18),*(undefined8 *)(param_1 + 8),
               *(undefined4 *)(param_1 + 0x20),param_2,param_3);
  }
  else {
    (**(code **)(**(longlong **)(param_1 + 0x10) + 0x50))();
  }
  return;
}



/* === FUN_0040e55c @ 0040e55c === */

void FUN_0040e55c(longlong param_1,undefined8 param_2,undefined8 param_3)

{
  if (*(longlong *)(param_1 + 0x10) == 0) {
    (**(code **)(**(longlong **)(param_1 + 0x18) + 0x60))
              (*(longlong **)(param_1 + 0x18),*(undefined8 *)(param_1 + 8),
               *(undefined4 *)(param_1 + 0x20),param_2,param_3);
  }
  else {
    (**(code **)(**(longlong **)(param_1 + 0x10) + 0x58))();
  }
  return;
}



/* === FUN_0040e59c @ 0040e59c === */

undefined8 FUN_0040e59c(longlong param_1,short *param_2,longlong *param_3,longlong *param_4)

{
  short sVar1;
  undefined1 auVar2 [16];
  SIZE_T uBytes;
  HLOCAL pvVar3;
  ulonglong uVar4;
  longlong lVar5;
  short *psVar6;
  undefined8 uVar7;
  
  uVar4 = 0xffffffffffffffff;
  uVar7 = 0x80004005;
  psVar6 = param_2;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    sVar1 = *psVar6;
    psVar6 = psVar6 + 1;
  } while (sVar1 != 0);
  auVar2._8_8_ = 0;
  auVar2._0_8_ = ~uVar4;
  uBytes = SUB168(ZEXT416(2) * auVar2,0);
  if (SUB168(ZEXT416(2) * auVar2,8) != 0) {
    uBytes = 0xffffffffffffffff;
  }
  if (uBytes == 0) {
    pvVar3 = (HLOCAL)0x0;
  }
  else {
    pvVar3 = LocalAlloc(0x40,uBytes);
  }
  *(HLOCAL *)(param_1 + 8) = pvVar3;
  if (pvVar3 != (HLOCAL)0x0) {
    lVar5 = (longlong)pvVar3 - (longlong)param_2;
    do {
      sVar1 = *param_2;
      *(short *)(lVar5 + (longlong)param_2) = sVar1;
      param_2 = param_2 + 1;
    } while (sVar1 != 0);
    if (param_3 == (longlong *)0x0) {
      if (param_4 == (longlong *)0x0) {
        return 0x80004005;
      }
      *(longlong **)(param_1 + 0x18) = param_4;
      lVar5 = *param_4;
      param_3 = param_4;
    }
    else {
      *(longlong **)(param_1 + 0x10) = param_3;
      lVar5 = *param_3;
    }
    (**(code **)(lVar5 + 8))(param_3);
    *(undefined4 *)(param_1 + 0x20) = 0;
    uVar7 = 0;
  }
  return uVar7;
}



/* === FUN_0040e668 @ 0040e668 === */

bool FUN_0040e668(void)

{
  bool bVar1;
  
  DAT_004106d8 = malloc(0x100);
  bVar1 = DAT_004106d8 != (undefined8 *)0x0;
  DAT_004106e0 = DAT_004106d8;
  if (bVar1) {
    *DAT_004106d8 = 0;
  }
  return !bVar1;
}



/* === FUN_0040e6a4 @ 0040e6a4 === */

undefined8 FUN_0040e6a4(undefined8 param_1,int param_2,undefined8 param_3)

{
  longlong lVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  bool bVar8;
  bool bVar9;
  
  iVar3 = 0;
  bVar8 = false;
  if (param_2 == 0) {
    if (DAT_00410140 < 1) {
      return 0;
    }
    DAT_00410140 = DAT_00410140 + -1;
    while( true ) {
      puVar7 = DAT_004106e0;
      LOCK();
      bVar8 = DAT_004106d0 == 0;
      if (bVar8) {
        DAT_004106d0 = 1;
      }
      UNLOCK();
      if (bVar8) break;
      Sleep(1000);
    }
    if (DAT_004106c8 == 2) {
      puVar6 = DAT_004106d8;
      if (DAT_004106e0 != (undefined8 *)0x0) {
        while (puVar6 = puVar6 + -1, puVar7 <= puVar6) {
          if ((code *)*puVar6 != (code *)0x0) {
            (*(code *)*puVar6)();
          }
        }
        free(puVar7);
        DAT_004106d8 = (undefined8 *)0x0;
        DAT_004106e0 = (undefined8 *)0x0;
      }
      DAT_004106c8 = 0;
      LOCK();
      DAT_004106d0 = 0;
      UNLOCK();
    }
    else {
      _amsg_exit(0x1f);
    }
  }
  else if (param_2 == 1) {
    lVar1 = *(longlong *)((longlong)Self + 8);
    while( true ) {
      lVar5 = 0;
      LOCK();
      bVar9 = DAT_004106d0 == 0;
      lVar2 = lVar1;
      if (!bVar9) {
        lVar5 = DAT_004106d0;
        lVar2 = DAT_004106d0;
      }
      DAT_004106d0 = lVar2;
      UNLOCK();
      if (bVar9) goto LAB_0040e7b2;
      if (lVar5 == lVar1) break;
      Sleep(1000);
    }
    bVar8 = true;
LAB_0040e7b2:
    if (DAT_004106c8 == 0) {
      puVar7 = &DAT_00401250;
      DAT_004106c8 = 1;
      do {
        if (iVar3 != 0) {
          return 0;
        }
        if ((code *)*puVar7 != (code *)0x0) {
          iVar3 = (*(code *)*puVar7)();
        }
        puVar7 = puVar7 + 1;
      } while (puVar7 < &DAT_00401260);
      if (iVar3 != 0) {
        return 0;
      }
      _initterm(&DAT_00401238,&DAT_00401248);
      DAT_004106c8 = 2;
    }
    else {
      _amsg_exit(0x1f);
    }
    if (!bVar8) {
      LOCK();
      DAT_004106d0 = 0;
      UNLOCK();
    }
    if ((DAT_004106f0 != (code *)0x0) && (uVar4 = FUN_0040ef60(0x4106f0), uVar4 != 0)) {
      (*DAT_004106f0)(param_1,2,param_3);
    }
    DAT_00410140 = DAT_00410140 + 1;
  }
  return 1;
}



/* === FUN_0040e87c @ 0040e87c === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0040e87c(undefined8 param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = (int)param_2;
  iVar4 = 1;
  if ((iVar3 == 0) && (DAT_00410140 == 0)) {
    iVar4 = 0;
  }
  else {
    _DAT_00410100 = iVar3;
    if ((iVar3 == 1) || (iVar3 == 2)) {
      if (DAT_004106e8 != (code *)0x0) {
        iVar4 = (*DAT_004106e8)(param_1,param_2,param_3,param_4,1);
      }
      iVar1 = 0;
      if (iVar4 != 0) {
        uVar2 = FUN_0040e6a4(param_1,iVar3,param_3);
        iVar1 = (int)uVar2;
      }
      if (iVar1 == 0) {
        _DAT_00410100 = 0xffffffff;
        return 0;
      }
    }
    uVar2 = FUN_00408270();
    iVar4 = (int)uVar2;
    if ((iVar3 == 1) && (iVar4 == 0)) {
      FUN_00408270();
      FUN_0040e6a4(param_1,0,0);
      if (DAT_004106e8 != (code *)0x0) {
        (*DAT_004106e8)(param_1,0,0);
      }
    }
    if ((iVar3 == 0) || (iVar3 == 3)) {
      uVar2 = FUN_0040e6a4(param_1,iVar3,param_3);
      iVar4 = (int)uVar2;
      if ((iVar4 != 0) && (DAT_004106e8 != (code *)0x0)) {
        iVar4 = (*DAT_004106e8)(param_1,param_2 & 0xffffffff,param_3);
      }
    }
  }
  _DAT_00410100 = 0xffffffff;
  return iVar4;
}



/* === FUN_0040ea5c @ 0040ea5c === */

undefined4 FUN_0040ea5c(undefined8 *param_1,longlong param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined8 **)(param_2 + 0x100) = param_1;
  uVar1 = *(undefined4 *)*param_1;
  *(undefined4 *)(param_2 + 0xa8) = uVar1;
  *(undefined8 **)(param_2 + 0xf8) = param_1;
  *(undefined4 *)(param_2 + 0x50) = uVar1;
  if (*(int *)(param_2 + 0x50) == -0x1f928c9d) {
    iVar2 = _XcptFilter(*(ulong *)(param_2 + 0x50),*(_EXCEPTION_POINTERS **)(param_2 + 0xf8));
    *(int *)(param_2 + 0x30) = iVar2;
  }
  else {
    *(undefined4 *)(param_2 + 0x30) = 0;
  }
  return *(undefined4 *)(param_2 + 0x30);
}



/* === FUN_0040eabc @ 0040eabc === */

undefined4 FUN_0040eabc(undefined8 *param_1,longlong param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined8 **)(param_2 + 0x110) = param_1;
  uVar1 = *(undefined4 *)*param_1;
  *(undefined4 *)(param_2 + 0x98) = uVar1;
  *(undefined8 **)(param_2 + 0xd0) = param_1;
  *(undefined4 *)(param_2 + 0x70) = uVar1;
  if (*(int *)(param_2 + 0x70) == -0x1f928c9d) {
    iVar2 = _XcptFilter(*(ulong *)(param_2 + 0x70),*(_EXCEPTION_POINTERS **)(param_2 + 0xd0));
    *(int *)(param_2 + 0x38) = iVar2;
  }
  else {
    *(undefined4 *)(param_2 + 0x38) = 0;
  }
  return *(undefined4 *)(param_2 + 0x38);
}



/* === FUN_0040eb1c @ 0040eb1c === */

undefined4 FUN_0040eb1c(undefined8 *param_1,longlong param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined8 **)(param_2 + 0x130) = param_1;
  uVar1 = *(undefined4 *)*param_1;
  *(undefined4 *)(param_2 + 0xcc) = uVar1;
  *(undefined8 **)(param_2 + 0xf0) = param_1;
  *(undefined4 *)(param_2 + 0x60) = uVar1;
  if (*(int *)(param_2 + 0x60) == -0x1f928c9d) {
    iVar2 = _XcptFilter(*(ulong *)(param_2 + 0x60),*(_EXCEPTION_POINTERS **)(param_2 + 0xf0));
    *(int *)(param_2 + 0x48) = iVar2;
  }
  else {
    *(undefined4 *)(param_2 + 0x48) = 0;
  }
  return *(undefined4 *)(param_2 + 0x48);
}



/* === FUN_0040eb7c @ 0040eb7c === */

undefined4 FUN_0040eb7c(undefined8 *param_1,longlong param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined8 **)(param_2 + 0x120) = param_1;
  uVar1 = *(undefined4 *)*param_1;
  *(undefined4 *)(param_2 + 0x8c) = uVar1;
  *(undefined8 **)(param_2 + 0xe0) = param_1;
  *(undefined4 *)(param_2 + 0x80) = uVar1;
  if (*(int *)(param_2 + 0x80) == -0x1f928c9d) {
    iVar2 = _XcptFilter(*(ulong *)(param_2 + 0x80),*(_EXCEPTION_POINTERS **)(param_2 + 0xe0));
    *(int *)(param_2 + 0x24) = iVar2;
  }
  else {
    *(undefined4 *)(param_2 + 0x24) = 0;
  }
  return *(undefined4 *)(param_2 + 0x24);
}



/* === FUN_0040ebdc @ 0040ebdc === */

undefined4 FUN_0040ebdc(undefined8 *param_1,longlong param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined8 **)(param_2 + 0x108) = param_1;
  uVar1 = *(undefined4 *)*param_1;
  *(undefined4 *)(param_2 + 0xd8) = uVar1;
  *(undefined8 **)(param_2 + 0x90) = param_1;
  *(undefined4 *)(param_2 + 0x28) = uVar1;
  if (*(int *)(param_2 + 0x28) == -0x1f928c9d) {
    iVar2 = _XcptFilter(*(ulong *)(param_2 + 0x28),*(_EXCEPTION_POINTERS **)(param_2 + 0x90));
    *(int *)(param_2 + 0x34) = iVar2;
  }
  else {
    *(undefined4 *)(param_2 + 0x34) = 0;
  }
  return *(undefined4 *)(param_2 + 0x34);
}



/* === FUN_0040ec3c @ 0040ec3c === */

undefined4 FUN_0040ec3c(undefined8 *param_1,longlong param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined8 **)(param_2 + 0x118) = param_1;
  uVar1 = *(undefined4 *)*param_1;
  *(undefined4 *)(param_2 + 0xb8) = uVar1;
  *(undefined8 **)(param_2 + 0xa0) = param_1;
  *(undefined4 *)(param_2 + 0x40) = uVar1;
  if (*(int *)(param_2 + 0x40) == -0x1f928c9d) {
    iVar2 = _XcptFilter(*(ulong *)(param_2 + 0x40),*(_EXCEPTION_POINTERS **)(param_2 + 0xa0));
    *(int *)(param_2 + 0x4c) = iVar2;
  }
  else {
    *(undefined4 *)(param_2 + 0x4c) = 0;
  }
  return *(undefined4 *)(param_2 + 0x4c);
}



/* === FUN_0040ec9c @ 0040ec9c === */

undefined4 FUN_0040ec9c(undefined8 *param_1,longlong param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined8 **)(param_2 + 0x128) = param_1;
  uVar1 = *(undefined4 *)*param_1;
  *(undefined4 *)(param_2 + 0xe8) = uVar1;
  *(undefined8 **)(param_2 + 0xb0) = param_1;
  *(undefined4 *)(param_2 + 0x58) = uVar1;
  if (*(int *)(param_2 + 0x58) == -0x1f928c9d) {
    iVar2 = _XcptFilter(*(ulong *)(param_2 + 0x58),*(_EXCEPTION_POINTERS **)(param_2 + 0xb0));
    *(int *)(param_2 + 0x68) = iVar2;
  }
  else {
    *(undefined4 *)(param_2 + 0x68) = 0;
  }
  return *(undefined4 *)(param_2 + 0x68);
}



/* === FUN_0040ecfc @ 0040ecfc === */

undefined4 FUN_0040ecfc(undefined8 *param_1,longlong param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined8 **)(param_2 + 0x138) = param_1;
  uVar1 = *(undefined4 *)*param_1;
  *(undefined4 *)(param_2 + 200) = uVar1;
  *(undefined8 **)(param_2 + 0xc0) = param_1;
  *(undefined4 *)(param_2 + 0x78) = uVar1;
  if (*(int *)(param_2 + 0x78) == -0x1f928c9d) {
    iVar2 = _XcptFilter(*(ulong *)(param_2 + 0x78),*(_EXCEPTION_POINTERS **)(param_2 + 0xc0));
    *(int *)(param_2 + 0x88) = iVar2;
  }
  else {
    *(undefined4 *)(param_2 + 0x88) = 0;
  }
  return *(undefined4 *)(param_2 + 0x88);
}



/* === FUN_0040ed5c @ 0040ed5c === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040ed5c(void)

{
  _DAT_00410100 = 0xffffffff;
  return;
}



/* === entry @ 0040ed7c === */

void entry(undefined8 param_1,uint param_2,undefined8 param_3,undefined8 param_4)

{
  if (param_2 == 1) {
    __security_init_cookie();
  }
  FUN_0040e87c(param_1,(ulonglong)param_2,param_3,param_4);
  return;
}



/* === FUN_0040edc0 @ 0040edc0 === */

_onexit_t FUN_0040edc0(_onexit_t param_1)

{
  _onexit_t p_Var1;
  longlong local_res10;
  undefined8 local_res18 [2];
  
  local_res10 = DAT_004106e0;
  if (DAT_004106e0 == -1) {
    p_Var1 = _onexit(param_1);
  }
  else {
    _lock(8);
    local_res10 = DAT_004106e0;
    local_res18[0] = DAT_004106d8;
    p_Var1 = (_onexit_t)__dllonexit(param_1,&local_res10,local_res18);
    DAT_004106e0 = local_res10;
    DAT_004106d8 = local_res18[0];
    _unlock(8);
  }
  return p_Var1;
}



/* === FUN_0040ee50 @ 0040ee50 === */

void FUN_0040ee50(void)

{
  _unlock(8);
  return;
}



/* === FUN_0040ee70 @ 0040ee70 === */

int FUN_0040ee70(_onexit_t param_1)

{
  _onexit_t p_Var1;
  
  p_Var1 = FUN_0040edc0(param_1);
  return (p_Var1 != (_onexit_t)0x0) - 1;
}



/* === FUN_0040eea0 @ 0040eea0 === */

void FUN_0040eea0(longlong param_1)

{
  if ((param_1 == DAT_00410108) && ((short)((ulonglong)param_1 >> 0x30) == 0)) {
    return;
  }
  FUN_0040f0e0(param_1);
  return;
}



/* === swprintf_s @ 0040eec6 === */

int __cdecl swprintf_s(wchar_t *_Dst,size_t _SizeInWords,wchar_t *_Format,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040eec6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = swprintf_s(_Dst,_SizeInWords,_Format);
  return iVar1;
}



/* === _XcptFilter @ 0040eed2 === */

int __cdecl _XcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040eed2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = _XcptFilter(_ExceptionNum,_ExceptionPtr);
  return iVar1;
}



/* === FUN_0040eee0 @ 0040eee0 === */

bool FUN_0040eee0(short *param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if ((*param_1 == 0x5a4d) &&
     (bVar1 = false, *(int *)((longlong)*(int *)(param_1 + 0x1e) + (longlong)param_1) == 0x4550)) {
    bVar1 = *(short *)((longlong)*(int *)(param_1 + 0x1e) + 0x18 + (longlong)param_1) == 0x20b;
  }
  return bVar1;
}



/* === _FindPESection @ 0040ef10 === */

/* Library Function - Single Match
    _FindPESection
   
   Library: Visual Studio 2005 Release */

PIMAGE_SECTION_HEADER __cdecl _FindPESection(PBYTE pImageBase,DWORD_PTR rva)

{
  int iVar1;
  PIMAGE_SECTION_HEADER p_Var2;
  uint uVar3;
  
  iVar1 = *(int *)(pImageBase + 0x3c);
  uVar3 = 0;
  p_Var2 = (PIMAGE_SECTION_HEADER)
           (pImageBase +
           (ulonglong)*(ushort *)(pImageBase + (longlong)iVar1 + 0x14) + 0x18 + (longlong)iVar1);
  if (*(ushort *)(pImageBase + (longlong)iVar1 + 6) != 0) {
    do {
      if ((p_Var2->VirtualAddress <= rva) &&
         (rva < (p_Var2->Misc).PhysicalAddress + p_Var2->VirtualAddress)) {
        return p_Var2;
      }
      uVar3 = uVar3 + 1;
      p_Var2 = p_Var2 + 1;
    } while (uVar3 < *(ushort *)(pImageBase + (longlong)iVar1 + 6));
  }
  return (PIMAGE_SECTION_HEADER)0x0;
}



/* === FUN_0040ef60 @ 0040ef60 === */

uint FUN_0040ef60(longlong param_1)

{
  bool bVar1;
  uint uVar2;
  undefined7 extraout_var;
  PIMAGE_SECTION_HEADER p_Var3;
  IMAGE_DOS_HEADER *pImageBase;
  
  pImageBase = &IMAGE_DOS_HEADER_00400000;
  bVar1 = FUN_0040eee0((short *)&IMAGE_DOS_HEADER_00400000);
  if ((int)CONCAT71(extraout_var,bVar1) == 0) {
    uVar2 = 0;
  }
  else {
    p_Var3 = _FindPESection((PBYTE)pImageBase,param_1 - (longlong)pImageBase);
    if (p_Var3 == (PIMAGE_SECTION_HEADER)0x0) {
      uVar2 = 0;
    }
    else {
      uVar2 = ~(p_Var3->Characteristics >> 0x1f) & 1;
    }
  }
  return uVar2;
}



/* === FUN_0040efb0 @ 0040efb0 === */

bool FUN_0040efb0(undefined8 *param_1)

{
  return *(int *)*param_1 == -0x3ffffffb;
}



/* === _initterm @ 0040efda === */

void _initterm(void)

{
                    /* WARNING: Could not recover jumptable at 0x0040efda. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _initterm();
  return;
}



/* === _amsg_exit @ 0040efe6 === */

void __cdecl _amsg_exit(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0040efe6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _amsg_exit(param_1);
  return;
}



/* === __security_init_cookie @ 0040f000 === */

/* Library Function - Single Match
    __security_init_cookie
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

void __cdecl __security_init_cookie(void)

{
  _FILETIME _Var1;
  DWORD DVar2;
  DWORD DVar3;
  DWORD DVar4;
  _FILETIME local_res8;
  LARGE_INTEGER local_res10;
  
  local_res8.dwLowDateTime = 0;
  local_res8.dwHighDateTime = 0;
  if (DAT_00410108 == 0x2b992ddfa232) {
    GetSystemTimeAsFileTime(&local_res8);
    _Var1 = local_res8;
    DVar2 = GetCurrentProcessId();
    DVar3 = GetCurrentThreadId();
    DVar4 = GetTickCount();
    QueryPerformanceCounter(&local_res10);
    DAT_00410108 = (local_res10.QuadPart ^
                   (ulonglong)_Var1 ^ (ulonglong)DVar2 ^ (ulonglong)DVar3 ^ (ulonglong)DVar4) &
                   0xffffffffffff;
    if (DAT_00410108 == 0x2b992ddfa232) {
      DAT_00410108 = 0x2b992ddfa233;
    }
  }
  DAT_00410110 = ~DAT_00410108;
  return;
}



/* === _unlock @ 0040f0ba === */

void __cdecl _unlock(int _File)

{
                    /* WARNING: Could not recover jumptable at 0x0040f0ba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _unlock(_File);
  return;
}



/* === __dllonexit @ 0040f0c6 === */

void __dllonexit(void)

{
                    /* WARNING: Could not recover jumptable at 0x0040f0c6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  __dllonexit();
  return;
}



/* === _lock @ 0040f0d2 === */

void __cdecl _lock(int _File)

{
                    /* WARNING: Could not recover jumptable at 0x0040f0d2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _lock(_File);
  return;
}



/* === FUN_0040f0e0 @ 0040f0e0 === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040f0e0(undefined8 param_1)

{
  HANDLE hProcess;
  DWORD64 unaff_retaddr;
  undefined8 local_res8 [4];
  PVOID local_48;
  ulonglong local_40;
  PRUNTIME_FUNCTION local_38;
  DWORD64 local_30;
  DWORD64 local_28;
  undefined8 local_20;
  undefined8 local_18;
  
  local_res8[0] = param_1;
  RtlCaptureContext(&DAT_004101f0);
  local_30 = DAT_004102e8;
  local_38 = RtlLookupFunctionEntry(DAT_004102e8,&local_28,(PUNWIND_HISTORY_TABLE)0x0);
  if (local_38 == (PRUNTIME_FUNCTION)0x0) {
    _DAT_00410288 = local_res8;
    DAT_004102e8 = unaff_retaddr;
  }
  else {
    RtlVirtualUnwind(0,local_28,local_30,local_38,(PCONTEXT)&DAT_004101f0,&local_48,&local_40,
                     (PKNONVOLATILE_CONTEXT_POINTERS)0x0);
  }
  _DAT_00410160 = DAT_004102e8;
  _DAT_00410270 = local_res8[0];
  _DAT_00410150 = 0xc0000409;
  _DAT_00410154 = 1;
  local_20 = DAT_00410108;
  local_18 = DAT_00410110;
  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)0x0);
  UnhandledExceptionFilter((_EXCEPTION_POINTERS *)&PTR_DAT_00401298);
  hProcess = GetCurrentProcess();
  TerminateProcess(hProcess,0xc0000409);
  return;
}



/* === RtlVirtualUnwind @ 0040f208 === */

PEXCEPTION_ROUTINE __stdcall
RtlVirtualUnwind(DWORD HandlerType,DWORD64 ImageBase,DWORD64 ControlPc,
                PRUNTIME_FUNCTION FunctionEntry,PCONTEXT ContextRecord,PVOID *HandlerData,
                PDWORD64 EstablisherFrame,PKNONVOLATILE_CONTEXT_POINTERS ContextPointers)

{
  PEXCEPTION_ROUTINE puVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040f208. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  puVar1 = RtlVirtualUnwind(HandlerType,ImageBase,ControlPc,FunctionEntry,ContextRecord,HandlerData,
                            EstablisherFrame,ContextPointers);
  return puVar1;
}



/* === RtlLookupFunctionEntry @ 0040f214 === */

PRUNTIME_FUNCTION __stdcall
RtlLookupFunctionEntry(DWORD64 ControlPc,PDWORD64 ImageBase,PUNWIND_HISTORY_TABLE HistoryTable)

{
  PRUNTIME_FUNCTION p_Var1;
  
                    /* WARNING: Could not recover jumptable at 0x0040f214. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  p_Var1 = RtlLookupFunctionEntry(ControlPc,ImageBase,HistoryTable);
  return p_Var1;
}



/* === HidD_GetAttributes @ 0040f220 === */

void HidD_GetAttributes(void)

{
                    /* WARNING: Could not recover jumptable at 0x0040f220. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  HidD_GetAttributes();
  return;
}



/* === HidD_GetHidGuid @ 0040f22c === */

void HidD_GetHidGuid(void)

{
                    /* WARNING: Could not recover jumptable at 0x0040f22c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  HidD_GetHidGuid();
  return;
}



/* === HidD_GetPreparsedData @ 0040f238 === */

void HidD_GetPreparsedData(void)

{
                    /* WARNING: Could not recover jumptable at 0x0040f238. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  HidD_GetPreparsedData();
  return;
}



/* === HidD_FreePreparsedData @ 0040f244 === */

void HidD_FreePreparsedData(void)

{
                    /* WARNING: Could not recover jumptable at 0x0040f244. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  HidD_FreePreparsedData();
  return;
}



/* === HidP_SetUsageValue @ 0040f250 === */

void HidP_SetUsageValue(void)

{
                    /* WARNING: Could not recover jumptable at 0x0040f250. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  HidP_SetUsageValue();
  return;
}



/* === __GSHandlerCheckCommon @ 0040f25c === */

/* Library Function - Single Match
    __GSHandlerCheckCommon
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release,
   Visual Studio 2019 Release */

void __GSHandlerCheckCommon(ulonglong param_1,longlong param_2,uint *param_3)

{
  longlong lVar1;
  ulonglong uVar2;
  
  uVar2 = param_1;
  if ((*param_3 & 4) != 0) {
    uVar2 = (longlong)(int)param_3[1] + param_1 & (longlong)(int)-param_3[2];
  }
  lVar1 = (ulonglong)*(uint *)(*(longlong *)(param_2 + 0x10) + 8) + *(longlong *)(param_2 + 8);
  if ((*(byte *)(lVar1 + 3) & 0xf) != 0) {
    param_1 = param_1 + (longlong)(int)(*(byte *)(lVar1 + 3) & 0xfffffff0);
  }
  FUN_0040eea0(param_1 ^ *(ulonglong *)((longlong)(int)(*param_3 & 0xfffffff8) + uVar2));
  return;
}



/* === __GSHandlerCheck @ 0040f2c8 === */

/* Library Function - Single Match
    __GSHandlerCheck
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release,
   Visual Studio 2019 Release */

undefined8
__GSHandlerCheck(undefined8 param_1,ulonglong param_2,undefined8 param_3,longlong param_4)

{
  __GSHandlerCheckCommon(param_2,param_4,*(uint **)(param_4 + 0x38));
  return 1;
}



/* === FUN_0040f2f0 @ 0040f2f0 === */

void FUN_0040f2f0(void)

{
  DAT_00410128 = CreateMutexW((LPSECURITY_ATTRIBUTES)0x0,0,
                              L"Global\\{1B28DA20-E753-46f7-8666-6C757D9EBD14}");
  DAT_00410120 = GetLastError();
  FUN_0040ee70(FUN_0040f330);
  return;
}



/* === FUN_0040f330 @ 0040f330 === */

void FUN_0040f330(void)

{
  PTR_PTR_00410118 = (undefined *)&PTR_FUN_00401728;
  if (DAT_00410128 != (HANDLE)0x0) {
    CloseHandle(DAT_00410128);
    DAT_00410128 = (HANDLE)0x0;
  }
  return;
}



