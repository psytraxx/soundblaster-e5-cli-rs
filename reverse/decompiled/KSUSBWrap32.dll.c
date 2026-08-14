/* === FUN_00402245 @ 00402245 === */

uint FUN_00402245(char *param_1,int *param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  char *pcVar7;
  
  *param_2 = 0;
  param_2[1] = 0;
  param_2[2] = 0;
  param_2[3] = 0;
  if (*param_1 == '{') {
    uVar6 = 0;
    pcVar7 = param_1 + 1;
    do {
      param_1 = pcVar7;
      *param_2 = *param_2 << 4;
      cVar1 = *param_1;
      if ((cVar1 < '0') || ('9' < cVar1)) {
        if ((cVar1 < 'a') || ('z' < cVar1)) {
          iVar3 = (int)cVar1;
        }
        else {
          iVar3 = cVar1 + -0x20;
        }
        iVar4 = (int)cVar1;
        if (0x40 < iVar3) {
          if ((cVar1 < 'a') || (iVar3 = iVar4 + -0x20, 'z' < cVar1)) {
            iVar3 = iVar4;
          }
          if (iVar3 < 0x47) {
            if (('`' < cVar1) && (cVar1 < '{')) {
              iVar4 = iVar4 + -0x20;
            }
            uVar2 = iVar4 - 0x37;
            goto LAB_004022cb;
          }
        }
        uVar2 = 0xff;
      }
      else {
        uVar2 = (int)cVar1 - 0x30;
      }
LAB_004022cb:
      if (0x10 < uVar2) {
        return 0x80004005;
      }
      uVar6 = uVar6 + 1;
      *param_2 = *param_2 + uVar2;
      pcVar7 = param_1 + 1;
    } while (uVar6 < 8);
    pcVar7 = param_1 + 2;
    if (param_1[1] == '-') {
      param_1 = (char *)0x0;
      do {
        pcVar5 = pcVar7;
        *(short *)(param_2 + 1) = (short)param_2[1] << 4;
        cVar1 = *pcVar5;
        if ((cVar1 < '0') || ('9' < cVar1)) {
          if ((cVar1 < 'a') || ('z' < cVar1)) {
            iVar3 = (int)cVar1;
          }
          else {
            iVar3 = cVar1 + -0x20;
          }
          iVar4 = (int)cVar1;
          if (0x40 < iVar3) {
            if ((cVar1 < 'a') || (iVar3 = iVar4 + -0x20, 'z' < cVar1)) {
              iVar3 = iVar4;
            }
            if (iVar3 < 0x47) {
              if (('`' < cVar1) && (cVar1 < '{')) {
                iVar4 = iVar4 + -0x20;
              }
              uVar6 = iVar4 - 0x37;
              goto LAB_0040234f;
            }
          }
          uVar6 = 0xff;
        }
        else {
          uVar6 = (int)cVar1 - 0x30;
        }
LAB_0040234f:
        if (0x10 < uVar6) {
          return 0x80004005;
        }
        param_1 = param_1 + 1;
        *(short *)(param_2 + 1) = (short)param_2[1] + (short)uVar6;
        pcVar7 = pcVar5 + 1;
      } while (param_1 < (char *)0x4);
      if (pcVar5[1] == '-') {
        uVar6 = 0;
        pcVar7 = pcVar5 + 2;
        do {
          param_1 = pcVar7;
          *(short *)((int)param_2 + 6) = *(short *)((int)param_2 + 6) << 4;
          cVar1 = *param_1;
          if ((cVar1 < '0') || ('9' < cVar1)) {
            if ((cVar1 < 'a') || ('z' < cVar1)) {
              iVar3 = (int)cVar1;
            }
            else {
              iVar3 = cVar1 + -0x20;
            }
            iVar4 = (int)cVar1;
            if (0x40 < iVar3) {
              if ((cVar1 < 'a') || (iVar3 = iVar4 + -0x20, 'z' < cVar1)) {
                iVar3 = iVar4;
              }
              if (iVar3 < 0x47) {
                if (('`' < cVar1) && (cVar1 < '{')) {
                  iVar4 = iVar4 + -0x20;
                }
                uVar2 = iVar4 - 0x37;
                goto LAB_004023d7;
              }
            }
            uVar2 = 0xff;
          }
          else {
            uVar2 = (int)cVar1 - 0x30;
          }
LAB_004023d7:
          if (0x10 < uVar2) {
            return 0x80004005;
          }
          uVar6 = uVar6 + 1;
          *(short *)((int)param_2 + 6) = *(short *)((int)param_2 + 6) + (short)uVar2;
          pcVar7 = param_1 + 1;
        } while (uVar6 < 4);
        if (param_1[1] == '-') {
          uVar6 = 0;
          pcVar7 = param_1 + 2;
          do {
            param_1 = pcVar7;
            cVar1 = *param_1;
            if ((cVar1 < '0') || ('9' < cVar1)) {
              if ((cVar1 < 'a') || ('z' < cVar1)) {
                iVar3 = (int)cVar1;
              }
              else {
                iVar3 = cVar1 + -0x20;
              }
              iVar4 = (int)cVar1;
              if (0x40 < iVar3) {
                if ((cVar1 < 'a') || (iVar3 = iVar4 + -0x20, 'z' < cVar1)) {
                  iVar3 = iVar4;
                }
                if (iVar3 < 0x47) {
                  if (('`' < cVar1) && (cVar1 < '{')) {
                    iVar4 = iVar4 + -0x20;
                  }
                  uVar2 = iVar4 - 0x37;
                  goto LAB_0040245f;
                }
              }
              uVar2 = 0xff;
            }
            else {
              uVar2 = (int)cVar1 - 0x30;
            }
LAB_0040245f:
            if (0x10 < uVar2) {
              return 0x80004005;
            }
            pcVar7 = (char *)(uVar6 + 8 + (int)param_2);
            *pcVar7 = (char)uVar2;
            cVar1 = param_1[1];
            if ((cVar1 < '0') || ('9' < cVar1)) {
              if ((cVar1 < 'a') || ('z' < cVar1)) {
                iVar3 = (int)cVar1;
              }
              else {
                iVar3 = cVar1 + -0x20;
              }
              iVar4 = (int)cVar1;
              if (0x40 < iVar3) {
                if ((cVar1 < 'a') || (iVar3 = iVar4 + -0x20, 'z' < cVar1)) {
                  iVar3 = iVar4;
                }
                if (iVar3 < 0x47) {
                  if (('`' < cVar1) && (cVar1 < '{')) {
                    iVar4 = iVar4 + -0x20;
                  }
                  uVar2 = iVar4 - 0x37;
                  goto LAB_004024c5;
                }
              }
              uVar2 = 0xff;
            }
            else {
              uVar2 = (int)cVar1 - 0x30;
            }
LAB_004024c5:
            if (0x10 < uVar2) {
              return 0x80004005;
            }
            uVar6 = uVar6 + 1;
            *pcVar7 = *pcVar7 * '\x10' + (char)uVar2;
            pcVar7 = param_1 + 2;
          } while (uVar6 < 2);
          pcVar7 = param_1 + 3;
          if (param_1[2] == '-') {
            pcVar5 = (char *)((int)param_2 + 10);
            do {
              cVar1 = *pcVar7;
              if ((cVar1 < '0') || ('9' < cVar1)) {
                if ((cVar1 < 'a') || ('z' < cVar1)) {
                  iVar3 = (int)cVar1;
                }
                else {
                  iVar3 = cVar1 + -0x20;
                }
                iVar4 = (int)cVar1;
                if (0x40 < iVar3) {
                  if ((cVar1 < 'a') || (iVar3 = iVar4 + -0x20, 'z' < cVar1)) {
                    iVar3 = iVar4;
                  }
                  if (iVar3 < 0x47) {
                    if (('`' < cVar1) && (cVar1 < '{')) {
                      iVar4 = iVar4 + -0x20;
                    }
                    uVar6 = iVar4 - 0x37;
                    goto LAB_00402561;
                  }
                }
                uVar6 = 0xff;
              }
              else {
                uVar6 = (int)cVar1 - 0x30;
              }
LAB_00402561:
              if (0x10 < uVar6) {
                return 0x80004005;
              }
              *pcVar5 = (char)uVar6;
              cVar1 = pcVar7[1];
              if ((cVar1 < '0') || ('9' < cVar1)) {
                if ((cVar1 < 'a') || ('z' < cVar1)) {
                  iVar3 = (int)cVar1;
                }
                else {
                  iVar3 = cVar1 + -0x20;
                }
                iVar4 = (int)cVar1;
                if (0x40 < iVar3) {
                  if ((cVar1 < 'a') || (iVar3 = iVar4 + -0x20, 'z' < cVar1)) {
                    iVar3 = iVar4;
                  }
                  if (iVar3 < 0x47) {
                    if (('`' < cVar1) && (cVar1 < '{')) {
                      iVar4 = iVar4 + -0x20;
                    }
                    uVar6 = iVar4 - 0x37;
                    goto LAB_004025bd;
                  }
                }
                uVar6 = 0xff;
              }
              else {
                uVar6 = (int)cVar1 - 0x30;
              }
LAB_004025bd:
              if (0x10 < uVar6) {
                return 0x80004005;
              }
              pcVar7 = pcVar7 + 2;
              *pcVar5 = *pcVar5 * '\x10' + (char)uVar6;
              pcVar5 = pcVar5 + 1;
              if ((char *)0x7 < pcVar5 + (-8 - (int)param_2)) {
                return -(uint)(*pcVar7 != '}') & 0x80004005;
              }
            } while( true );
          }
        }
      }
    }
  }
  return 0x80004005;
}



/* === FUN_004025fb @ 004025fb === */

undefined4 FUN_004025fb(undefined4 *param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  
  if ((int)((ulonglong)param_2 * (ulonglong)param_3 >> 0x20) == 0) {
    *param_1 = (int)((ulonglong)param_2 * (ulonglong)param_3);
    uVar1 = 0;
  }
  else {
    uVar1 = 0x80070057;
  }
  return uVar1;
}



/* === FUN_00402626 @ 00402626 === */

LPVOID FUN_00402626(uint param_1,uint param_2)

{
  int iVar1;
  LPVOID pvVar2;
  SIZE_T local_8;
  
  local_8 = 0;
  iVar1 = FUN_004025fb(&local_8,param_1,param_2);
  if (iVar1 < 0) {
    pvVar2 = (LPVOID)0x0;
  }
  else {
    pvVar2 = CoTaskMemAlloc(local_8);
  }
  return pvVar2;
}



/* === FUN_00402659 @ 00402659 === */

LPVOID FUN_00402659(LPVOID param_1,uint param_2,uint param_3)

{
  int iVar1;
  LPVOID pvVar2;
  SIZE_T local_8;
  
  local_8 = 0;
  iVar1 = FUN_004025fb(&local_8,param_2,param_3);
  if (iVar1 < 0) {
    pvVar2 = (LPVOID)0x0;
  }
  else {
    pvVar2 = CoTaskMemRealloc(param_1,local_8);
  }
  return pvVar2;
}



/* === FUN_0040268f @ 0040268f === */

void FUN_0040268f(size_t param_1)

{
  malloc(param_1);
  return;
}



/* === FUN_004026a7 @ 004026a7 === */

void FUN_004026a7(void *param_1)

{
  free(param_1);
  return;
}



/* === FUN_004026bf @ 004026bf === */

bool FUN_004026bf(void *param_1,int param_2,LPCWSTR param_3)

{
  int iVar1;
  errno_t eVar2;
  
  iVar1 = lstrlenW(param_3);
  eVar2 = memcpy_s(param_1,param_2 * 2,param_3,iVar1 * 2 + 2);
  return (bool)('\x01' - (eVar2 != 0));
}



/* === FUN_004026f4 @ 004026f4 === */

void FUN_004026f4(DWORD param_1,DWORD param_2)

{
  RaiseException(param_1,param_2,0,(ULONG_PTR *)0x0);
  return;
}



/* === FUN_00402712 @ 00402712 === */

void FUN_00402712(int param_1)

{
  code *pcVar1;
  
  FUN_004026f4(((param_1 == -0x7ff8fff2) - 1 & 6) + 0xc0000017,1);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}



/* === FUN_0040273a @ 0040273a === */

void FUN_0040273a(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    return;
  }
  if (param_1 == 0xc) {
    iVar1 = -0x7ff8fff2;
  }
  else {
    if (param_1 == 0x16) goto LAB_00402764;
    if (param_1 == 0x22) goto LAB_00402764;
    if (param_1 == 0x50) {
      return;
    }
    iVar1 = -0x7fffbffb;
  }
  do {
    FUN_00402712(iVar1);
LAB_00402764:
    iVar1 = -0x7ff8ffa9;
  } while( true );
}



/* === FUN_0040277b @ 0040277b === */

void __cdecl FUN_0040277b(void *param_1,rsize_t param_2,void *param_3,rsize_t param_4)

{
  errno_t eVar1;
  
  eVar1 = memcpy_s(param_1,param_2,param_3,param_4);
  FUN_0040273a(eVar1);
  return;
}



/* === FUN_004027a1 @ 004027a1 === */

void __cdecl FUN_004027a1(void *param_1,rsize_t param_2,void *param_3,rsize_t param_4)

{
  errno_t eVar1;
  
  eVar1 = memmove_s(param_1,param_2,param_3,param_4);
  FUN_0040273a(eVar1);
  return;
}



/* === FUN_004027c7 @ 004027c7 === */

undefined4 * __fastcall FUN_004027c7(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return param_1;
}



/* === Init @ 004027de === */

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    public: long __thiscall ATL::CComCriticalSection::Init(void)
   
   Libraries: Visual Studio 2005 Release, Visual Studio 2008 Release */

long __thiscall ATL::CComCriticalSection::Init(CComCriticalSection *this)

{
  InitializeCriticalSection((LPCRITICAL_SECTION)this);
  return 0;
}



/* === FUN_0040282e @ 0040282e === */

void __fastcall FUN_0040282e(CComCriticalSection *param_1)

{
  long lVar1;
  
  lVar1 = ATL::CComCriticalSection::Init(param_1);
  if (-1 < lVar1) {
    param_1[0x18] = (CComCriticalSection)0x1;
  }
  return;
}



/* === FUN_00402847 @ 00402847 === */

DWORD FUN_00402847(void)

{
  DWORD DVar1;
  
  DVar1 = GetLastError();
  if (0 < (int)DVar1) {
    DVar1 = DVar1 & 0xffff | 0x80070000;
  }
  return DVar1;
}



/* === FUN_00402861 @ 00402861 === */

uint FUN_00402861(uint param_1)

{
  if (0 < (int)param_1) {
    param_1 = param_1 & 0xffff | 0x80070000;
  }
  return param_1;
}



/* === FUN_00402880 @ 00402880 === */

int * FUN_00402880(int *param_1,int *param_2)

{
  int *piVar1;
  
  if (param_1 == (int *)0x0) {
    param_2 = (int *)0x0;
  }
  else {
    if (param_2 != (int *)0x0) {
      (**(code **)(*param_2 + 4))(param_2);
    }
    piVar1 = (int *)*param_1;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
    }
    *param_1 = (int)param_2;
  }
  return param_2;
}



/* === FUN_004028ba @ 004028ba === */

void FUN_004028ba(int param_1,int param_2,short *param_3)

{
  uint uVar1;
  
  if (param_2 != 0) {
    uVar1 = 0;
    if (param_2 != 1) {
      do {
        if (*param_3 == 0) break;
        *(short *)(param_1 + uVar1 * 2) = *param_3;
        if ((*param_3 == 0x27) && (uVar1 < param_2 - 2U)) {
          uVar1 = uVar1 + 1;
          *(undefined2 *)(param_1 + uVar1 * 2) = 0x27;
        }
        param_3 = param_3 + 1;
        uVar1 = uVar1 + 1;
      } while (uVar1 < param_2 - 1U);
    }
    *(undefined2 *)(param_1 + uVar1 * 2) = 0;
  }
  return;
}



/* === Close @ 00402910 === */

/* Library Function - Single Match
    public: long __thiscall ATL::CRegKey::Close(void)
   
   Library: Visual Studio 2005 Release */

long __thiscall ATL::CRegKey::Close(CRegKey *this)

{
  long lVar1;
  
  lVar1 = 0;
  if (*(HKEY *)this != (HKEY)0x0) {
    lVar1 = RegCloseKey(*(HKEY *)this);
    *(undefined4 *)this = 0;
  }
  return lVar1;
}



/* === Create @ 0040292e === */

/* Library Function - Multiple Matches With Same Base Name
    public: long __thiscall ATL::CRegKey::Create(struct HKEY__ *,char const *,char *,unsigned
   long,unsigned long,struct _SECURITY_ATTRIBUTES *,unsigned long *)
    public: long __thiscall ATL::CRegKey::Create(struct HKEY__ *,wchar_t const *,wchar_t *,unsigned
   long,unsigned long,struct _SECURITY_ATTRIBUTES *,unsigned long *)
   
   Library: Visual Studio 2005 Release */

void __thiscall
Create(void *this,HKEY param_1,LPCWSTR param_2,LPWSTR param_3,DWORD param_4,REGSAM param_5,
      LPSECURITY_ATTRIBUTES param_6,undefined4 *param_7)

{
  LSTATUS LVar1;
  HKEY local_8;
  
  local_8 = (HKEY)0x0;
  LVar1 = RegCreateKeyExW(param_1,param_2,0,param_3,param_4,param_5,param_6,&local_8,
                          (LPDWORD)&param_6);
  if (param_7 != (undefined4 *)0x0) {
    *param_7 = param_6;
  }
  if (LVar1 == 0) {
    ATL::CRegKey::Close(this);
    *(HKEY *)this = local_8;
  }
  return;
}



/* === FUN_00402983 @ 00402983 === */

void __thiscall FUN_00402983(void *this,HKEY param_1,LPCWSTR param_2,REGSAM param_3)

{
  LSTATUS LVar1;
  HKEY local_8;
  
  local_8 = (HKEY)0x0;
  LVar1 = RegOpenKeyExW(param_1,param_2,0,param_3,&local_8);
  if (LVar1 == 0) {
    ATL::CRegKey::Close(this);
    *(HKEY *)this = local_8;
  }
  return;
}



/* === SetDWORDValue @ 004029bf === */

/* Library Function - Multiple Matches With Same Base Name
    public: long __thiscall ATL::CRegKey::SetDWORDValue(char const *,unsigned long)
    public: long __thiscall ATL::CRegKey::SetDWORDValue(wchar_t const *,unsigned long)
   
   Libraries: Visual Studio 2010 Release, Visual Studio 2012 Release, Visual Studio 2015 Release */

void __thiscall SetDWORDValue(void *this,LPCWSTR param_1)

{
  RegSetValueExW(*(HKEY *)this,param_1,0,4,&stack0x00000008,4);
  return;
}



/* === FUN_004029e2 @ 004029e2 === */

void __thiscall FUN_004029e2(void *this,LPCWSTR param_1,LPCWSTR param_2,DWORD param_3)

{
  int iVar1;
  
  if (param_2 == (LPCWSTR)0x0) {
    FUN_00402712(-0x7fffbffb);
  }
  iVar1 = lstrlenW(param_2);
  RegSetValueExW(*(HKEY *)this,param_1,0,param_3,(BYTE *)param_2,iVar1 * 2 + 2);
  return;
}



/* === FUN_00402a25 @ 00402a25 === */

void __thiscall FUN_00402a25(void *this,LPCWSTR param_1,LPCWSTR param_2)

{
  int iVar1;
  LPCWSTR lpString;
  DWORD cbData;
  
  if (param_2 == (LPCWSTR)0x0) {
    FUN_00402712(-0x7fffbffb);
  }
  cbData = 0;
  lpString = param_2;
  do {
    iVar1 = lstrlenW(lpString);
    iVar1 = iVar1 + 1;
    lpString = lpString + iVar1;
    cbData = cbData + iVar1 * 2;
  } while (iVar1 != 1);
  RegSetValueExW(*(HKEY *)this,param_1,0,7,(BYTE *)param_2,cbData);
  return;
}



/* === FUN_00402a75 @ 00402a75 === */

undefined4 FUN_00402a75(LPCWSTR param_1,LPCWSTR param_2)

{
  int iVar1;
  
  iVar1 = lstrcmpiW(param_1,param_2);
  return CONCAT31((int3)((uint)-iVar1 >> 8),'\x01' - (iVar1 != 0));
}



/* === FUN_00402a95 @ 00402a95 === */

undefined4 __fastcall FUN_00402a95(undefined4 *param_1)

{
  LPWSTR pWVar1;
  
  if (*(LPCWSTR)*param_1 == L'\'') {
    pWVar1 = CharNextW((LPCWSTR)*param_1);
    if (*pWVar1 != L'\'') {
      return 1;
    }
  }
  return 0;
}



/* === FUN_00402ab6 @ 00402ab6 === */

undefined4 * __thiscall FUN_00402ab6(void *this,uint param_1)

{
  undefined2 *puVar1;
  
  if ((int)param_1 < 100) {
    param_1 = 1000;
  }
  *(undefined4 *)this = 0;
  *(uint *)((int)this + 4) = param_1;
  puVar1 = FUN_00402626(param_1,2);
  *(undefined2 **)((int)this + 8) = puVar1;
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0;
  }
  return this;
}



/* === FUN_00402af0 @ 00402af0 === */

undefined4 __thiscall FUN_00402af0(void *this,void *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  LPVOID pvVar3;
  uint uVar4;
  
  iVar1 = *(int *)this + 1 + param_2;
  if ((*(int *)this < iVar1) && (param_2 < iVar1)) {
    uVar4 = *(uint *)((int)this + 4);
    if ((int)uVar4 <= iVar1) {
      do {
        if (0x3fffffff < (int)uVar4) {
          return 0;
        }
        uVar4 = uVar4 * 2;
      } while ((int)uVar4 <= iVar1);
      pvVar3 = FUN_00402659(*(LPVOID *)((int)this + 8),uVar4,2);
      if (pvVar3 == (LPVOID)0x0) {
        return 0;
      }
      *(LPVOID *)((int)this + 8) = pvVar3;
      *(uint *)((int)this + 4) = uVar4;
    }
    iVar1 = *(int *)this;
    if (((-1 < iVar1) && (iVar2 = *(int *)((int)this + 4), iVar1 < iVar2)) &&
       (iVar2 - iVar1 <= iVar2)) {
      FUN_0040277b((void *)(*(int *)((int)this + 8) + iVar1 * 2),(iVar2 - iVar1) * 2,param_1,
                   param_2 * 2);
      *(int *)this = *(int *)this + param_2;
      *(undefined2 *)(*(int *)((int)this + 8) + *(int *)this * 2) = 0;
      return 1;
    }
  }
  return 0;
}



/* === FUN_00402b82 @ 00402b82 === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00402b82(LPCWSTR param_1,undefined2 *param_2)

{
  int iVar1;
  uint uVar2;
  
  if ((_DAT_0040d0d0 & 1) == 0) {
    _DAT_0040d0d0 = _DAT_0040d0d0 | 1;
    DAT_0040d0b0 = &DAT_00401328;
    DAT_0040d0b4 = 8;
    DAT_0040d0b8 = &DAT_00401324;
    _DAT_0040d0bc = 0x4008;
    _DAT_0040d0c0 = &DAT_00401320;
    _DAT_0040d0c4 = 0x13;
    _DAT_0040d0c8 = &DAT_0040131c;
    _DAT_0040d0cc = 0x11;
  }
  uVar2 = 0;
  do {
    iVar1 = lstrcmpiW(param_1,(LPCWSTR)(&DAT_0040d0b0)[uVar2 * 2]);
    if (iVar1 == 0) {
      *param_2 = (&DAT_0040d0b4)[uVar2 * 4];
      return 1;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 4);
  return 0;
}



/* === FUN_00402c1f @ 00402c1f === */

int FUN_00402c1f(ushort param_1)

{
  uint uVar1;
  
  uVar1 = (uint)param_1;
  if (0x2f < uVar1) {
    if (uVar1 < 0x3a) {
      return uVar1 - 0x30;
    }
    if (0x40 < uVar1) {
      if (uVar1 < 0x47) {
        return uVar1 - 0x37;
      }
      if (uVar1 - 0x61 < 6) {
        return uVar1 - 0x57;
      }
    }
  }
  return (uint)(byte)(param_1 >> 8) << 8;
}



/* === FUN_00402c5e @ 00402c5e === */

undefined4 FUN_00402c5e(LPCWSTR param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    iVar1 = lstrcmpiW(param_1,(LPCWSTR)(&PTR_u_HKCR_004013f0)[uVar2 * 2]);
    if (iVar1 == 0) {
      return (&DAT_004013f4)[uVar2 * 2];
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0xe);
  return 0;
}



/* === FUN_00402c95 @ 00402c95 === */

LPCWSTR FUN_00402c95(LPCWSTR param_1,WCHAR param_2)

{
  LPCWSTR pWVar1;
  
  pWVar1 = param_1;
  if (param_1 != (LPCWSTR)0x0) {
    for (; (pWVar1 = (LPCWSTR)0x0, *param_1 != L'\0' && (pWVar1 = param_1, *param_1 != param_2));
        param_1 = CharNextW(param_1)) {
    }
  }
  return pWVar1;
}



/* === FUN_00402ccb @ 00402ccb === */

undefined4 FUN_00402ccb(ushort param_1)

{
  undefined4 uVar1;
  
  if ((param_1 < 9) || (((10 < param_1 && (param_1 != 0xd)) && (param_1 != 0x20)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



/* === FUN_00402cf8 @ 00402cf8 === */

void __fastcall FUN_00402cf8(undefined4 *param_1)

{
  LPWSTR pWVar1;
  int iVar2;
  
  while( true ) {
    iVar2 = FUN_00402ccb(*(ushort *)*param_1);
    if (iVar2 == 0) break;
    pWVar1 = CharNextW((LPCWSTR)*param_1);
    *param_1 = pWVar1;
  }
  return;
}



/* === FUN_00402d21 @ 00402d21 === */

undefined4 __thiscall FUN_00402d21(void *this,WCHAR *param_1)

{
  WCHAR WVar1;
  undefined4 uVar2;
  LPWSTR pWVar3;
  int iVar4;
  LPCWSTR pWVar5;
  WCHAR *pWVar6;
  
  FUN_00402cf8(this);
  WVar1 = **(LPCWSTR *)this;
  if (WVar1 == L'\0') {
    uVar2 = 0x80020009;
  }
  else {
    pWVar6 = param_1;
    if (WVar1 == L'\'') {
      pWVar3 = CharNextW(*(LPCWSTR *)this);
      *(LPWSTR *)this = pWVar3;
      while ((*pWVar3 != L'\0' && (iVar4 = FUN_00402a95(this), iVar4 == 0))) {
        if (**(LPCWSTR *)this == L'\'') {
          pWVar3 = CharNextW(*(LPCWSTR *)this);
          *(LPWSTR *)this = pWVar3;
        }
        pWVar5 = *(LPCWSTR *)this;
        pWVar3 = CharNextW(pWVar5);
        *(LPWSTR *)this = pWVar3;
        iVar4 = (int)pWVar3 - (int)pWVar5 >> 1;
        if (param_1 + 0x1000 <= pWVar6 + iVar4 + 1) {
          return 0x80020009;
        }
        if (0 < iVar4) {
          do {
            *pWVar6 = *pWVar5;
            pWVar6 = pWVar6 + 1;
            pWVar5 = pWVar5 + 1;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
        pWVar3 = *(LPWSTR *)this;
      }
      if (**(short **)this == 0) {
        return 0x80020009;
      }
      *pWVar6 = L'\0';
      pWVar3 = CharNextW(*(LPCWSTR *)this);
      *(LPWSTR *)this = pWVar3;
    }
    else {
      do {
        pWVar5 = *(LPCWSTR *)this;
        iVar4 = FUN_00402ccb(*pWVar5);
        if (iVar4 != 0) break;
        pWVar3 = CharNextW(pWVar5);
        *(LPWSTR *)this = pWVar3;
        iVar4 = (int)pWVar3 - (int)pWVar5 >> 1;
        if (param_1 + 0x1000 <= pWVar6 + iVar4 + 1) {
          return 0x80020009;
        }
        if (0 < iVar4) {
          do {
            *pWVar6 = *pWVar5;
            pWVar6 = pWVar6 + 1;
            pWVar5 = pWVar5 + 1;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
      } while (**(short **)this != 0);
      *pWVar6 = L'\0';
    }
    uVar2 = 0;
  }
  return uVar2;
}



/* === FUN_00402e2b @ 00402e2b === */

undefined4 FUN_00402e2b(LPCWSTR param_1)

{
  int iVar1;
  undefined **ppuVar2;
  
  ppuVar2 = &PTR_u_AppID_0040135c;
  do {
    iVar1 = lstrcmpiW(param_1,(LPCWSTR)*ppuVar2);
    if (iVar1 == 0) {
      return 0;
    }
    ppuVar2 = ppuVar2 + 1;
  } while ((int)ppuVar2 < 0x40138c);
  return 1;
}



/* === FUN_00402e61 @ 00402e61 === */

bool FUN_00402e61(HKEY param_1)

{
  LSTATUS LVar1;
  DWORD local_8;
  
  local_8 = 0;
  LVar1 = RegQueryInfoKeyW(param_1,(LPWSTR)0x0,(LPDWORD)0x0,(LPDWORD)0x0,&local_8,(LPDWORD)0x0,
                           (LPDWORD)0x0,(LPDWORD)0x0,(LPDWORD)0x0,(LPDWORD)0x0,(LPDWORD)0x0,
                           (PFILETIME)0x0);
  return LVar1 == 0 && local_8 != 0;
}



/* === FUN_00402e9d @ 00402e9d === */

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void __fastcall FUN_00402e9d(undefined4 *param_1,undefined4 param_2,WCHAR *param_3)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  WCHAR local_2008 [4096];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  if ((*param_3 == L'=') &&
     (iVar1 = FUN_00402d21(param_1,param_3), param_2 = extraout_EDX, -1 < iVar1)) {
    FUN_00402cf8(param_1);
    iVar1 = FUN_00402d21(param_1,local_2008);
    param_2 = extraout_EDX_00;
    if (-1 < iVar1) {
      FUN_00402d21(param_1,param_3);
      param_2 = extraout_EDX_01;
    }
  }
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,param_2);
  return;
}



/* === FUN_00402f11 @ 00402f11 === */

void __cdecl FUN_00402f11(SIZE_T param_1)

{
  if (param_1 != 0) {
    LocalAlloc(0x40,param_1);
  }
  return;
}



/* === FUN_00402f2f @ 00402f2f === */

void __cdecl FUN_00402f2f(HLOCAL param_1)

{
  if (param_1 != (HLOCAL)0x0) {
    LocalFree(param_1);
  }
  return;
}



/* === FUN_00402f4a @ 00402f4a === */

undefined4 * __fastcall FUN_00402f4a(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  *param_1 = 0;
  puVar2 = param_1;
  for (iVar1 = 6; puVar2 = puVar2 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
  }
  *(undefined1 *)(param_1 + 7) = 0;
  return param_1;
}



/* === FUN_00402f6c @ 00402f6c === */

undefined4 FUN_00402f6c(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x2c) = param_2;
  return 0;
}



/* === FUN_00402f85 @ 00402f85 === */

undefined4 FUN_00402f85(int param_1,int *param_2)

{
  undefined4 uVar1;
  int *local_8;
  
  local_8 = (int *)0x0;
  uVar1 = 0x80004005;
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else if (param_2 != (int *)0x0) {
    uVar1 = (**(code **)(*param_2 + 0x1c))(param_2,param_1,param_1,&local_8);
    if (local_8 != (int *)0x0) {
      (**(code **)(*local_8 + 8))(local_8);
    }
  }
  return uVar1;
}



/* === FUN_00402fd1 @ 00402fd1 === */

void __fastcall FUN_00402fd1(int *param_1)

{
  int *piVar1;
  
  while (*param_1 != 0) {
    piVar1 = (int *)*param_1;
    *param_1 = *piVar1;
    FUN_004026a7(piVar1);
  }
  return;
}



/* === FUN_00402ff0 @ 00402ff0 === */

void __fastcall FUN_00402ff0(undefined4 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    free((void *)*param_1);
    *param_1 = 0;
  }
  if ((void *)param_1[1] != (void *)0x0) {
    free((void *)param_1[1]);
    param_1[1] = 0;
  }
  param_1[2] = 0;
  return;
}



/* === FUN_00403024 @ 00403024 === */

int __thiscall FUN_00403024(void *this,int param_1)

{
  code *pcVar1;
  int iVar2;
  
  if ((-1 < param_1) && (param_1 < *(int *)((int)this + 8))) {
    return *(int *)this + param_1 * 4;
  }
  RaiseException(0xc000008c,1,0,(ULONG_PTR *)0x0);
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}



/* === FUN_00403055 @ 00403055 === */

int __thiscall FUN_00403055(void *this,int param_1)

{
  code *pcVar1;
  int iVar2;
  
  if ((-1 < param_1) && (param_1 < *(int *)((int)this + 8))) {
    return *(int *)((int)this + 4) + param_1 * 4;
  }
  RaiseException(0xc000008c,1,0,(ULONG_PTR *)0x0);
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}



/* === FUN_00403087 @ 00403087 === */

void __fastcall FUN_00403087(int param_1)

{
  if (*(char *)(param_1 + 0x1c) != '\0') {
    *(undefined1 *)(param_1 + 0x1c) = 0;
    DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 4));
  }
  return;
}



/* === FUN_004030a9 @ 004030a9 === */

int __thiscall FUN_004030a9(void *this,undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < *(int *)((int)this + 8)) {
    do {
      uVar1 = FUN_00402a75(*(LPCWSTR *)(*(int *)this + iVar2 * 4),(LPCWSTR)*param_1);
      if ((char)uVar1 != '\0') {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)((int)this + 8));
  }
  return -1;
}



/* === FUN_004030e4 @ 004030e4 === */

void __fastcall FUN_004030e4(undefined4 *param_1)

{
  FUN_004026a7((void *)*param_1);
  return;
}



/* === FUN_004030f1 @ 004030f1 === */

void __thiscall FUN_004030f1(void *this,size_t param_1)

{
  int iVar1;
  
  iVar1 = FUN_0040268f(param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_00402712(-0x7ff8fff2);
  }
  *(int *)this = iVar1;
  return;
}



/* === FUN_0040311b @ 0040311b === */

void __thiscall FUN_0040311b(void *this,uint param_1,undefined4 *param_2)

{
  int *extraout_ECX;
  
  if (*(uint *)((int)this + 4) <= param_1) {
    param_1 = FUN_00402712(-0x7ff8ffa9);
    this = extraout_ECX;
  }
  *(undefined4 *)(*(int *)this + param_1 * 4) = *param_2;
  return;
}



/* === FUN_00403145 @ 00403145 === */

int __thiscall FUN_00403145(void *this,uint param_1)

{
  int *extraout_ECX;
  
  if (*(uint *)((int)this + 4) <= param_1) {
    param_1 = FUN_00402712(-0x7ff8ffa9);
    this = extraout_ECX;
  }
  return *(int *)this + param_1 * 4;
}



/* === FUN_0040316a @ 0040316a === */

void __thiscall FUN_0040316a(void *this,uint param_1,undefined4 *param_2)

{
  int *extraout_ECX;
  int iVar1;
  undefined4 *puVar2;
  
  if (*(uint *)((int)this + 4) <= param_1) {
    FUN_00402712(-0x7ff8ffa9);
    this = extraout_ECX;
  }
  puVar2 = (undefined4 *)(param_1 * 0x18 + *(int *)this);
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}



/* === FUN_0040319b @ 0040319b === */

int __thiscall FUN_0040319b(void *this,uint param_1)

{
  int *extraout_ECX;
  
  if (*(uint *)((int)this + 4) <= param_1) {
    param_1 = FUN_00402712(-0x7ff8ffa9);
    this = extraout_ECX;
  }
  return param_1 * 0x18 + *(int *)this;
}



/* === FUN_004031c0 @ 004031c0 === */

uint FUN_004031c0(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = FUN_004025fb(&param_2,param_1,param_2);
  if (iVar1 < 0) {
    FUN_00402712(iVar1);
  }
  return param_2;
}



/* === FUN_004031ea @ 004031ea === */

void FUN_004031ea(void *param_1,void *param_2,int param_3)

{
  FUN_004027a1(param_1,param_3 << 2,param_2,param_3 << 2);
  return;
}



/* === FUN_0040320e @ 0040320e === */

void FUN_0040320e(void *param_1,void *param_2,int param_3)

{
  FUN_004027a1(param_1,param_3 * 0x18,param_2,param_3 * 0x18);
  return;
}



/* === FUN_00403232 @ 00403232 === */

void __thiscall FUN_00403232(void *this,LPCWSTR param_1)

{
  int iVar1;
  LSTATUS LVar2;
  undefined4 extraout_EDX;
  undefined4 uVar3;
  undefined4 extraout_EDX_00;
  _FILETIME local_21c;
  LPCWSTR local_214;
  DWORD local_210;
  HKEY local_20c;
  WCHAR local_208 [256];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_214 = param_1;
  local_20c = (HKEY)0x0;
  iVar1 = FUN_00402983(&local_20c,*(HKEY *)this,param_1,0x2001f);
  if (iVar1 == 0) {
    do {
      local_210 = 0x100;
      LVar2 = RegEnumKeyExW(local_20c,0,local_208,&local_210,(LPDWORD)0x0,(LPWSTR)0x0,(LPDWORD)0x0,
                            &local_21c);
      if (LVar2 != 0) {
        ATL::CRegKey::Close((CRegKey *)&local_20c);
        RegDeleteKeyW(*(HKEY *)this,local_214);
        break;
      }
      iVar1 = FUN_00403232(&local_20c,local_208);
    } while (iVar1 == 0);
    ATL::CRegKey::Close((CRegKey *)&local_20c);
    uVar3 = extraout_EDX_00;
  }
  else {
    ATL::CRegKey::Close((CRegKey *)&local_20c);
    uVar3 = extraout_EDX;
  }
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar3);
  return;
}



/* === FUN_00403313 @ 00403313 === */

undefined4 __fastcall FUN_00403313(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < (int)param_1[2]) {
    do {
      puVar1 = (undefined4 *)FUN_00403024(param_1,iVar2);
      FUN_00402f2f((HLOCAL)*puVar1);
      puVar1 = (undefined4 *)FUN_00403055(param_1,iVar2);
      FUN_00402f2f((HLOCAL)*puVar1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)param_1[2]);
  }
  FUN_00402ff0(param_1);
  return 0;
}



/* === FUN_00403357 @ 00403357 === */

undefined4 __thiscall FUN_00403357(void *this,LPCWSTR param_1)

{
  undefined4 uVar1;
  int iVar2;
  int local_8;
  
  if (param_1 == (LPCWSTR)0x0) {
    uVar1 = 0;
  }
  else {
    local_8 = 0;
    iVar2 = lstrlenW(param_1);
    uVar1 = FUN_00402af0(this,param_1,iVar2);
    FUN_00402fd1(&local_8);
  }
  return uVar1;
}



/* === FUN_00403398 @ 00403398 === */

undefined4 FUN_00403398(int param_1)

{
  undefined4 uVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  uVar1 = FUN_00403313((undefined4 *)(param_1 + 4));
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  return uVar1;
}



/* === InlineIsEqualUnknown @ 004033ca === */

/* Library Function - Single Match
    int __stdcall ATL::InlineIsEqualUnknown(struct _GUID const &)
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

int ATL::InlineIsEqualUnknown(_GUID *param_1)

{
  int iVar1;
  
  if ((((param_1->Data1 == 0) &&
       (iVar1._0_2_ = param_1->Data2, iVar1._2_2_ = param_1->Data3, iVar1 == 0)) &&
      (*(int *)param_1->Data4 == 0xc0)) && (*(int *)(param_1->Data4 + 4) == 0x46000000)) {
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}



/* === FUN_004033ff @ 004033ff === */

undefined4 FUN_004033ff(int param_1,int param_2,_GUID *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 0x80004003;
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = 0;
    if ((param_2 != 0) && (iVar2 = ATL::InlineIsEqualUnknown(param_3), iVar2 == 0)) {
      return 0x80040110;
    }
    uVar1 = (**(code **)(param_1 + 0x24))(param_2,param_3,param_4);
  }
  return uVar1;
}



/* === FUN_00403444 @ 00403444 === */

undefined4 FUN_00403444(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    (**(code **)(*DAT_0040d09c + 8))();
  }
  else {
    (**(code **)(*DAT_0040d09c + 4))();
  }
  return 0;
}



/* === FUN_0040346a @ 0040346a === */

int FUN_0040346a(short *param_1,uint param_2,int param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  if ((param_2 == 0) || (0x7fffffff < param_2)) {
    iVar2 = -0x7ff8ffa9;
  }
  if (iVar2 < 0) {
    return iVar2;
  }
  iVar2 = 0;
  if (param_2 != 0) {
    iVar4 = 0x7ffffffe - param_2;
    iVar3 = param_3 - (int)param_1;
    do {
      if ((iVar4 + param_2 == 0) || (sVar1 = *(short *)(iVar3 + (int)param_1), sVar1 == 0)) break;
      *param_1 = sVar1;
      param_1 = param_1 + 1;
      param_2 = param_2 - 1;
    } while (param_2 != 0);
    if (param_2 != 0) goto LAB_004034c7;
  }
  param_1 = param_1 + -1;
  iVar2 = -0x7ff8ff86;
LAB_004034c7:
  *param_1 = 0;
  return iVar2;
}



/* === FUN_004034d8 @ 004034d8 === */

int FUN_004034d8(int param_1)

{
  void *this;
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int local_8;
  
  iVar1 = param_1;
  uVar5 = 0;
  local_8 = 0;
  if (*(int *)(param_1 + 0x488) == 0) {
    local_8 = CBaseAudioProcessingObject::UnlockForProcess();
  }
  else if (*(int *)(param_1 + 0x488) != 0) {
    this = (void *)(param_1 + 0x4f0);
    do {
      puVar2 = (undefined4 *)FUN_00403145((void *)(iVar1 + 0x4ac),uVar5);
      iVar3 = (**(code **)(*(int *)*puVar2 + 0x10))((int *)*puVar2);
      if (iVar3 < 0) {
        local_8 = iVar3;
      }
      piVar4 = (int *)FUN_00403145((void *)(iVar1 + 0x4e0),uVar5);
      piVar4 = (int *)*piVar4;
      if (piVar4 != (int *)0x0) {
        (**(code **)(*piVar4 + 8))(piVar4);
        param_1 = 0;
        FUN_0040311b((void *)(iVar1 + 0x4e0),uVar5,&param_1);
      }
      puVar2 = (undefined4 *)FUN_00403145(this,uVar5);
      if ((HLOCAL)*puVar2 != (HLOCAL)0x0) {
        LocalFree((HLOCAL)*puVar2);
        param_1 = 0;
        FUN_0040311b(this,uVar5,&param_1);
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(iVar1 + 0x488));
  }
  return local_8;
}



/* === FUN_00403592 @ 00403592 === */

int FUN_00403592(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_8;
  
  uVar3 = 0;
  local_8 = 0;
  if (*(int *)(param_1 + 0x490) == 0) {
    local_8 = FUN_00409ded();
  }
  else if (*(int *)(param_1 + 0x490) != 0) {
    do {
      puVar1 = (undefined4 *)FUN_00403145((void *)(param_1 + 0x4a4),uVar3);
      iVar2 = (**(code **)(*(int *)*puVar1 + 0xc))((int *)*puVar1);
      if (iVar2 < 0) {
        local_8 = iVar2;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(param_1 + 0x490));
  }
  return local_8;
}



/* === FUN_004035ef @ 004035ef === */

int FUN_004035ef(int param_1,uint *param_2)

{
  uint uVar1;
  uint *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint local_10;
  int local_c;
  int local_8;
  
  puVar2 = param_2;
  *param_2 = 0;
  param_2[1] = 0;
  local_8 = 0;
  local_10 = 0;
  local_c = 0;
  if (*(int *)(param_1 + 0x490) == 0) {
    local_8 = FUN_00409df7(param_1,param_2);
  }
  else {
    param_2 = (uint *)0x0;
    if (*(int *)(param_1 + 0x490) != 0) {
      do {
        puVar3 = (undefined4 *)FUN_00403145((void *)(param_1 + 0x4a4),(uint)param_2);
        iVar4 = (**(code **)(*(int *)*puVar3 + 0x10))((int *)*puVar3,&local_10);
        if (-1 < iVar4) {
          uVar1 = *puVar2;
          *puVar2 = *puVar2 + local_10;
          puVar2[1] = puVar2[1] + local_c + (uint)CARRY4(uVar1,local_10);
          iVar4 = local_8;
        }
        local_8 = iVar4;
        param_2 = (uint *)((int)param_2 + 1);
      } while (param_2 < *(uint **)(param_1 + 0x490));
    }
  }
  return local_8;
}



/* === FUN_00403676 @ 00403676 === */

int FUN_00403676(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int *hMem;
  undefined4 *puVar3;
  uint uVar4;
  int local_8;
  
  piVar2 = param_2;
  local_8 = 0;
  if (*(int *)(param_1 + 0x490) == 0) {
    local_8 = FUN_00409e4c(param_1,param_2);
  }
  else {
    hMem = LocalAlloc(0x40,4);
    if (hMem != (int *)0x0) {
      puVar3 = CoTaskMemAlloc(0x444);
      *param_2 = (int)puVar3;
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = *(undefined4 *)(param_1 + 0x6c);
        puVar3[1] = *(undefined4 *)(param_1 + 0x70);
        puVar3[2] = *(undefined4 *)(param_1 + 0x74);
        puVar3[3] = *(undefined4 *)(param_1 + 0x78);
        FUN_0040346a((short *)(*param_2 + 0x14),0x200,param_1 + 0x7c);
        FUN_0040346a((short *)(*param_2 + 0x214),0x200,param_1 + 0x27c);
        *(undefined4 *)(*param_2 + 0x414) = 1;
        *(undefined4 *)(*param_2 + 0x418) = 0;
        *(undefined4 *)(*param_2 + 0x430) = 1;
        iVar1 = *param_2;
        *(undefined4 *)(iVar1 + 0x434) = *(undefined4 *)(param_1 + 0x47c);
        *(undefined4 *)(iVar1 + 0x438) = *(undefined4 *)(param_1 + 0x480);
        *(undefined4 *)(iVar1 + 0x43c) = *(undefined4 *)(param_1 + 0x484);
        *(undefined4 *)(iVar1 + 0x440) = *(undefined4 *)(param_1 + 0x488);
        param_2 = (int *)0x0;
        if (*(int *)(param_1 + 0x490) != 0) {
          do {
            if (local_8 < 0) break;
            puVar3 = (undefined4 *)FUN_00403145((void *)(param_1 + 0x4a4),(uint)param_2);
            local_8 = (**(code **)(*(int *)*puVar3 + 0x14))((int *)*puVar3,hMem);
            if (-1 < local_8) {
              if (param_2 == (int *)0x0) {
                *(undefined4 *)(*piVar2 + 0x10) = *(undefined4 *)(*hMem + 0x10);
                *(undefined4 *)(*piVar2 + 0x41c) = *(undefined4 *)(*hMem + 0x41c);
                *(undefined4 *)(*piVar2 + 0x420) = *(undefined4 *)(*hMem + 0x420);
                *(undefined4 *)(*piVar2 + 0x424) = *(undefined4 *)(*hMem + 0x424);
                *(undefined4 *)(*piVar2 + 0x428) = *(undefined4 *)(*hMem + 0x428);
                *(undefined4 *)(*piVar2 + 0x42c) = *(undefined4 *)(*hMem + 0x42c);
              }
              else {
                *(uint *)(*piVar2 + 0x10) = *(uint *)(*piVar2 + 0x10) & *(uint *)(*hMem + 0x10);
                uVar4 = *(uint *)(*piVar2 + 0x41c);
                if (uVar4 <= *(uint *)(*hMem + 0x41c)) {
                  uVar4 = *(uint *)(*hMem + 0x41c);
                }
                *(uint *)(*piVar2 + 0x41c) = uVar4;
                uVar4 = *(uint *)(*piVar2 + 0x420);
                if (*(uint *)(*hMem + 0x420) <= uVar4) {
                  uVar4 = *(uint *)(*hMem + 0x420);
                }
                *(uint *)(*piVar2 + 0x420) = uVar4;
                uVar4 = *(uint *)(*piVar2 + 0x424);
                if (uVar4 <= *(uint *)(*hMem + 0x424)) {
                  uVar4 = *(uint *)(*hMem + 0x424);
                }
                *(uint *)(*piVar2 + 0x424) = uVar4;
                uVar4 = *(uint *)(*piVar2 + 0x428);
                if (*(uint *)(*hMem + 0x428) <= uVar4) {
                  uVar4 = *(uint *)(*hMem + 0x428);
                }
                *(uint *)(*piVar2 + 0x428) = uVar4;
                uVar4 = *(uint *)(*piVar2 + 0x42c);
                if (*(uint *)(*hMem + 0x42c) <= uVar4) {
                  uVar4 = *(uint *)(*hMem + 0x42c);
                }
                *(uint *)(*piVar2 + 0x42c) = uVar4;
              }
            }
            if ((LPVOID)*hMem != (LPVOID)0x0) {
              CoTaskMemFree((LPVOID)*hMem);
              *hMem = 0;
            }
            param_2 = (int *)((int)param_2 + 1);
          } while (param_2 < *(int **)(param_1 + 0x490));
        }
      }
      LocalFree(hMem);
    }
  }
  return local_8;
}



/* === FUN_0040389b @ 0040389b === */

int FUN_0040389b(int param_1,int *param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  int local_c;
  int local_8;
  
  uVar4 = 0;
  local_8 = 0;
  local_c = 0;
  if (*(int *)(param_1 + 0x490) == 0) {
    local_8 = FUN_00409e1a(param_1,param_2);
  }
  else if (*(int *)(param_1 + 0x490) != 0) {
    do {
      puVar2 = (undefined4 *)FUN_00403145((void *)(param_1 + 0x4a4),uVar4);
      piVar1 = (int *)*puVar2;
      if (uVar4 == 0) {
        iVar3 = (**(code **)(*piVar1 + 0x24))(piVar1,param_2);
      }
      else {
        iVar3 = (**(code **)(*piVar1 + 0x24))(piVar1,&local_c);
        if ((-1 < iVar3) && (iVar3 = local_8, *param_2 != local_c)) {
          local_8 = -0x7fffbffb;
          iVar3 = local_8;
        }
      }
      local_8 = iVar3;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(param_1 + 0x490));
  }
  return local_8;
}



/* === FUN_00403921 @ 00403921 === */

undefined4 __thiscall FUN_00403921(void *this,int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int *piVar3;
  uint uVar4;
  
  piVar1 = param_1;
  uVar4 = 0;
  if (param_1 == (int *)0x0) {
    uVar2 = 0x80004003;
  }
  else {
    *param_1 = 0;
    param_1 = (int *)0x0;
    if (*(int *)((int)this + 0x490) != 0) {
      do {
        piVar3 = (int *)FUN_00403145((void *)((int)this + 0x4c4),uVar4);
        piVar3 = (int *)*piVar3;
        if (piVar3 != (int *)0x0) {
          param_1 = (int *)0x0;
          (**(code **)(*piVar3 + 0xc))(piVar3,&param_1);
          *piVar1 = *piVar1 + (int)param_1;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(uint *)((int)this + 0x490));
    }
    uVar2 = 0;
  }
  return uVar2;
}



/* === FUN_00403986 @ 00403986 === */

undefined4 __thiscall FUN_00403986(void *this,uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint local_14 [2];
  int *local_c [2];
  
  uVar4 = 0;
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    local_c[0] = (int *)0x0;
    local_c[1] = (int *)0x0;
    local_14[0] = 0;
    local_14[1] = 0;
    if (*(int *)((int)this + 0x490) != 0) {
      do {
        piVar2 = (int *)FUN_00403145((void *)((int)this + 0x4c4),uVar4);
        piVar2 = (int *)*piVar2;
        local_c[uVar4] = piVar2;
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 0xc))(piVar2,local_14 + uVar4);
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(uint *)((int)this + 0x490));
    }
    *param_2 = 0;
    piVar2 = local_c[0];
    if (*(int *)((int)this + 0x490) == 2) {
      if (param_1 < local_14[0]) {
        if (local_c[0] == (int *)0x0) {
          return 0x80070057;
        }
      }
      else {
        if (local_c[1] == (int *)0x0) {
          return 0x80070057;
        }
        param_1 = param_1 - local_14[0];
        piVar2 = local_c[1];
      }
      iVar3 = *piVar2;
    }
    else {
      if (*(int *)((int)this + 0x490) != 1) {
        return 0x80070057;
      }
      if (local_c[0] == (int *)0x0) {
        return 0x80070057;
      }
      iVar3 = *local_c[0];
    }
    uVar1 = (**(code **)(iVar3 + 0x10))(piVar2,param_1,param_2);
  }
  return uVar1;
}



/* === FUN_00403a44 @ 00403a44 === */

undefined4 __thiscall FUN_00403a44(void *this,uint param_1,int param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint local_14 [2];
  int *local_c [2];
  
  uVar4 = 0;
  if (param_2 == 0) {
    uVar1 = 0x80004003;
  }
  else {
    local_c[0] = (int *)0x0;
    local_c[1] = (int *)0x0;
    local_14[0] = 0;
    local_14[1] = 0;
    if (*(int *)((int)this + 0x490) != 0) {
      do {
        piVar2 = (int *)FUN_00403145((void *)((int)this + 0x4c4),uVar4);
        piVar2 = (int *)*piVar2;
        local_c[uVar4] = piVar2;
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 0xc))(piVar2,local_14 + uVar4);
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(uint *)((int)this + 0x490));
    }
    piVar2 = local_c[0];
    if (*(int *)((int)this + 0x490) == 2) {
      if (param_1 < local_14[0]) {
        if (local_c[0] == (int *)0x0) {
          return 0x80070057;
        }
      }
      else {
        if (local_c[1] == (int *)0x0) {
          return 0x80070057;
        }
        param_1 = param_1 - local_14[0];
        piVar2 = local_c[1];
      }
      iVar3 = *piVar2;
    }
    else {
      if (*(int *)((int)this + 0x490) != 1) {
        return 0x80070057;
      }
      if (local_c[0] == (int *)0x0) {
        return 0x80070057;
      }
      iVar3 = *local_c[0];
    }
    uVar1 = (**(code **)(iVar3 + 0x14))(piVar2,param_1,param_2);
  }
  return uVar1;
}



/* === FUN_00403afe @ 00403afe === */

int * __thiscall FUN_00403afe(void *this,int *param_1,int *param_2,int param_3,int *param_4)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int *local_14;
  int *local_10;
  int *local_c;
  void *local_8;
  
  local_14 = (int *)0x0;
  local_10 = (int *)0x0;
  local_c = (int *)0x0;
  local_8 = this;
  if (*(int *)((int)this + 0x490) != 2) {
    puVar2 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),0);
    piVar5 = (int *)(**(code **)(*(int *)*puVar2 + 0x1c))((int *)*puVar2,param_1,param_2,param_4);
    return piVar5;
  }
  puVar2 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),0);
  piVar5 = (int *)*puVar2;
  puVar2 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),1);
  piVar1 = param_4;
  piVar6 = (int *)*puVar2;
  iVar3 = (**(code **)(*piVar5 + 0x1c))(piVar5,param_1,param_2,param_4);
  if (iVar3 == 0) {
    piVar4 = param_2;
    if (param_1 != (int *)0x0) {
      piVar4 = param_1;
    }
    param_4 = (int *)FUN_00402f85((int)piVar4,piVar6);
    if (param_4 != (int *)0x0) {
LAB_00403ba7:
      (**(code **)(*(int *)*piVar1 + 8))((int *)*piVar1);
      *piVar1 = 0;
      goto LAB_00403bb2;
    }
    if (param_3 == 0) goto LAB_00403d60;
    FUN_0040311b((void *)((int)local_8 + 0x4e8),0,&param_1);
    piVar5 = param_1;
  }
  else {
    if (iVar3 == 1) {
      local_14 = (int *)*piVar1;
      (**(code **)(*local_14 + 4))(local_14);
      goto LAB_00403ba7;
    }
LAB_00403bb2:
    iVar3 = FUN_00402f85((int)param_2,piVar5);
    if (iVar3 == 0) {
      param_4 = (int *)(**(code **)(*piVar6 + 0x1c))(piVar6,param_1,param_2,piVar1);
      if (param_4 != (int *)0x0) {
        if (param_4 == (int *)0x1) {
          local_10 = (int *)*piVar1;
          (**(code **)(*local_10 + 4))(local_10);
          (**(code **)(*(int *)*piVar1 + 8))((int *)*piVar1);
          *piVar1 = 0;
          local_c = local_10;
          (**(code **)(*local_10 + 4))(local_10);
        }
        goto LAB_00403c28;
      }
      param_4 = (int *)0x0;
    }
    else {
LAB_00403c28:
      if ((local_10 == (int *)0x0) &&
         ((**(code **)(*piVar6 + 0x1c))(piVar6,param_1,param_2,&local_10), local_10 == (int *)0x0))
      {
        param_4 = (int *)0x80004005;
      }
      else {
        param_4 = (int *)(**(code **)(*piVar5 + 0x1c))(piVar5,local_10,param_2,piVar1);
      }
      if (param_4 != (int *)0x0) {
        if ((int)param_4 < 0) {
          iVar3 = FUN_00402f85((int)param_1,piVar6);
          if (iVar3 == 0) {
            piVar4 = local_14;
            if (local_14 == (int *)0x0) {
              param_4 = (int *)(**(code **)(*piVar5 + 0x1c))(piVar5,local_10,param_2,piVar1);
              if ((-1 < (int)param_4) ||
                 ((local_10 == (int *)0x0 &&
                  (param_4 = (int *)(**(code **)(*piVar6 + 0x1c))(piVar6,param_1,param_2,&local_10),
                  param_4 != (int *)0x1)))) goto LAB_00403d60;
              iVar3 = FUN_00402f85((int)local_10,piVar5);
              piVar4 = local_10;
              if (iVar3 != 0) {
                piVar4 = (int *)*piVar1;
                if (piVar4 != (int *)0x0) {
                  (**(code **)(*piVar4 + 8))(piVar4);
                  *piVar1 = 0;
                }
                iVar3 = (**(code **)(*piVar5 + 0x1c))(piVar5,param_1,param_2,piVar1);
                if (iVar3 < 0) {
                  param_4 = (int *)(**(code **)(*piVar6 + 0x1c))(piVar6,param_1,param_2,piVar1);
                  if ((int)param_4 < 0) goto LAB_00403d60;
                  piVar4 = (int *)*piVar1;
                  piVar6 = piVar5;
                  if (piVar4 != (int *)0x0) {
                    (**(code **)(*piVar4 + 8))(piVar4);
                    *piVar1 = 0;
                  }
                }
                else {
                  piVar5 = (int *)*piVar1;
                  if (piVar5 != (int *)0x0) {
                    (**(code **)(*piVar5 + 8))(piVar5);
                    *piVar1 = 0;
                  }
                }
                param_4 = (int *)FUN_00402f85((int)param_2,piVar6);
                goto LAB_00403d60;
              }
            }
            *piVar1 = (int)piVar4;
            (**(code **)(*piVar4 + 4))(piVar4);
            param_4 = (int *)0x1;
          }
          else {
            param_4 = (int *)0x887d0003;
          }
        }
        goto LAB_00403d60;
      }
    }
    if (param_3 == 0) goto LAB_00403d60;
    FUN_0040311b((void *)((int)local_8 + 0x4e8),0,&param_2);
    piVar5 = param_2;
  }
  (**(code **)(*piVar5 + 4))(piVar5);
LAB_00403d60:
  if (local_14 != (int *)0x0) {
    (**(code **)(*local_14 + 8))(local_14);
  }
  if (local_10 != (int *)0x0) {
    (**(code **)(*local_10 + 8))(local_10);
    local_10 = (int *)0x0;
  }
  piVar5 = local_c;
  if ((int)param_4 < 0) {
    piVar5 = (int *)*piVar1;
    if (piVar5 != (int *)0x0) {
      (**(code **)(*piVar5 + 8))(piVar5);
      *piVar1 = 0;
    }
    piVar5 = local_c;
    if (local_c == (int *)0x0) {
      return param_4;
    }
    *piVar1 = (int)local_c;
    (**(code **)(*local_c + 4))(local_c);
    param_4 = (int *)0x1;
  }
  if (piVar5 != (int *)0x0) {
    (**(code **)(*piVar5 + 8))(piVar5);
  }
  return param_4;
}



/* === FUN_00403ded @ 00403ded === */

int __thiscall FUN_00403ded(void *this,int *param_1,int *param_2,int param_3,int *param_4)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int *local_14;
  int *local_10;
  int *local_c;
  void *local_8;
  
  local_14 = (int *)0x0;
  local_10 = (int *)0x0;
  local_c = (int *)0x0;
  local_8 = this;
  if (*(int *)((int)this + 0x490) != 2) {
    puVar3 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),0);
    iVar4 = (**(code **)(*(int *)*puVar3 + 0x20))((int *)*puVar3,param_1,param_2,param_4);
    return iVar4;
  }
  puVar3 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),0);
  piVar5 = (int *)*puVar3;
  puVar3 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),1);
  piVar2 = param_4;
  piVar1 = (int *)*puVar3;
  iVar4 = (**(code **)(*piVar5 + 0x20))(piVar5,param_1,param_2,param_4);
  if (iVar4 == 0) {
    piVar7 = param_1;
    if (param_2 != (int *)0x0) {
      piVar7 = param_2;
    }
    iVar4 = FUN_00402f85((int)piVar7,piVar1);
    if (iVar4 != 0) {
LAB_00403e97:
      (**(code **)(*(int *)*piVar2 + 8))((int *)*piVar2);
      *piVar2 = 0;
      goto LAB_00403ea2;
    }
    iVar6 = 0;
    if (param_3 == 0) goto LAB_00404051;
    FUN_0040311b((void *)((int)local_8 + 0x4e8),0,piVar2);
    piVar5 = (int *)*piVar2;
LAB_00404001:
    (**(code **)(*piVar5 + 4))(piVar5);
  }
  else {
    if (iVar4 == 1) {
      local_14 = (int *)*piVar2;
      (**(code **)(*local_14 + 4))(local_14);
      goto LAB_00403e97;
    }
LAB_00403ea2:
    if ((local_14 != (int *)0x0) ||
       (iVar4 = (**(code **)(*piVar5 + 0x20))(piVar5,param_1,param_2,&local_14),
       local_14 != (int *)0x0)) {
      iVar4 = (**(code **)(*piVar1 + 0x20))(piVar1,local_14,param_2,piVar2);
      if (iVar4 == 0) {
        iVar6 = 0;
        if (param_3 != 0) {
          FUN_0040311b((void *)((int)local_8 + 0x4e8),0,&local_14);
          piVar5 = local_14;
          goto LAB_00404001;
        }
        goto LAB_00404051;
      }
      piVar7 = (int *)*piVar2;
      if (piVar7 != (int *)0x0) {
        (**(code **)(*piVar7 + 8))(piVar7);
        *piVar2 = 0;
      }
    }
    iVar6 = 0;
    if (iVar4 != 0) {
      iVar4 = FUN_00402f85((int)param_1,piVar5);
      if (iVar4 == 0) {
        iVar4 = (**(code **)(*piVar1 + 0x20))(piVar1,param_1,param_2,piVar2);
        if (iVar4 == 0) {
          iVar6 = 0;
          if (param_3 != 0) {
            FUN_0040311b((void *)((int)local_8 + 0x4e8),0,&param_1);
            piVar5 = param_1;
            goto LAB_00404001;
          }
          goto LAB_00404051;
        }
        if (iVar4 == 1) {
          local_10 = (int *)*piVar2;
          (**(code **)(*local_10 + 4))(local_10);
          (**(code **)(*(int *)*piVar2 + 8))((int *)*piVar2);
          *piVar2 = 0;
          local_c = local_10;
          (**(code **)(*local_10 + 4))(local_10);
        }
      }
      if ((local_14 == (int *)0x0) &&
         (iVar6 = (**(code **)(*piVar5 + 0x20))(piVar5,param_1,param_2,&local_14),
         local_14 == (int *)0x0)) goto LAB_00404062;
      iVar4 = FUN_00402f85((int)local_14,piVar1);
      if (iVar4 == 0) {
        *piVar2 = (int)local_14;
        (**(code **)(*local_14 + 4))(local_14);
        iVar6 = 1;
      }
      else {
        iVar4 = FUN_00402f85((int)param_1,piVar5);
        if (iVar4 == 0) {
          if (local_10 == (int *)0x0) {
            iVar6 = (**(code **)(*piVar1 + 0x20))(piVar1,param_1,param_2,&local_10);
          }
          else {
            iVar6 = 1;
          }
          if (-1 < iVar6) {
            *piVar2 = (int)local_10;
            piVar5 = local_10;
            goto LAB_00404001;
          }
          piVar7 = (int *)*piVar2;
          if (piVar7 != (int *)0x0) {
            (**(code **)(*piVar7 + 8))(piVar7);
            *piVar2 = 0;
          }
          iVar6 = (**(code **)(*piVar5 + 0x20))(piVar5,param_1,param_2,piVar2);
          if (-1 < iVar6) {
            piVar5 = (int *)*piVar2;
            if (piVar5 != (int *)0x0) {
              (**(code **)(*piVar5 + 8))(piVar5);
              *piVar2 = 0;
            }
            iVar6 = FUN_00402f85((int)param_2,piVar1);
          }
        }
        else {
          iVar6 = -0x7782fffd;
        }
      }
    }
  }
LAB_00404051:
  if (local_14 != (int *)0x0) {
    (**(code **)(*local_14 + 8))(local_14);
    local_14 = (int *)0x0;
  }
LAB_00404062:
  if (local_10 != (int *)0x0) {
    (**(code **)(*local_10 + 8))(local_10);
    local_10 = (int *)0x0;
  }
  piVar5 = local_c;
  if (iVar6 < 0) {
    piVar5 = (int *)*piVar2;
    if (piVar5 != (int *)0x0) {
      (**(code **)(*piVar5 + 8))(piVar5);
      *piVar2 = 0;
    }
    piVar5 = local_c;
    if (local_c == (int *)0x0) {
      return iVar6;
    }
    *piVar2 = (int)local_c;
    (**(code **)(*local_c + 4))(local_c);
    iVar6 = 1;
  }
  if (piVar5 != (int *)0x0) {
    (**(code **)(*piVar5 + 8))(piVar5);
  }
  return iVar6;
}



/* === FUN_004040d5 @ 004040d5 === */

undefined4 __thiscall FUN_004040d5(void *this,undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  iVar1 = FUN_004030a9(this,param_1);
  if (iVar1 == -1) {
    uVar2 = 0;
  }
  else {
    puVar3 = (undefined4 *)FUN_00403055(this,iVar1);
    uVar2 = *puVar3;
  }
  return uVar2;
}



/* === FUN_00404102 @ 00404102 === */

void __thiscall FUN_00404102(void *this,int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(*(int *)this + param_1 * 4);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *param_2;
  }
  puVar1 = (undefined4 *)(*(int *)((int)this + 4) + param_1 * 4);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *param_3;
  }
  return;
}



/* === FUN_00404133 @ 00404133 === */

int __thiscall FUN_00404133(void *this,uint param_1)

{
  if (param_1 < 0x401) {
    *(int *)this = (int)this + 4;
  }
  else {
    FUN_004030f1(this,param_1);
  }
  return *(int *)this;
}



/* === FUN_0040415f @ 0040415f === */

int __thiscall FUN_0040415f(void *this,uint param_1)

{
  if (param_1 < 0x101) {
    *(int *)this = (int)this + 4;
  }
  else {
    FUN_004030f1(this,param_1);
  }
  return *(int *)this;
}



/* === FUN_0040418b @ 0040418b === */

void __fastcall FUN_0040418b(undefined4 *param_1)

{
  param_1[1] = 0xc0000001;
  *param_1 = &PTR_LAB_004015a8;
  FUN_00403087((int)(param_1 + 1));
  return;
}



/* === FUN_004041a6 @ 004041a6 === */

undefined4 * __fastcall FUN_004041a6(undefined4 *param_1)

{
  FUN_00402f4a(param_1 + 1);
  *param_1 = &PTR_LAB_004015a8;
  return param_1;
}



/* === FUN_004041c2 @ 004041c2 === */

void __fastcall FUN_004041c2(undefined4 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    free((void *)*param_1);
  }
  return;
}



/* === FUN_004041d6 @ 004041d6 === */

undefined4 __thiscall FUN_004041d6(void *this,uint param_1)

{
  void *in_EAX;
  undefined4 uVar1;
  uint uVar2;
  void *pvVar3;
  void *extraout_EAX;
  
  if (*(uint *)((int)this + 8) < param_1) {
    uVar2 = *(uint *)((int)this + 0xc);
    if (*(int *)this == 0) {
      if (param_1 < uVar2) {
        param_1 = uVar2;
      }
      in_EAX = calloc(param_1,4);
      *(void **)this = in_EAX;
      if (in_EAX != (void *)0x0) {
        *(uint *)((int)this + 8) = param_1;
        goto LAB_00404265;
      }
    }
    else {
      if (uVar2 == 0) {
        uVar2 = *(uint *)((int)this + 4) >> 3;
        if (uVar2 < 4) {
          uVar2 = 4;
        }
        else if (0x400 < uVar2) {
          uVar2 = 0x400;
        }
      }
      uVar2 = uVar2 + *(uint *)((int)this + 8);
      if (uVar2 <= param_1) {
        uVar2 = param_1;
      }
      pvVar3 = calloc(uVar2,4);
      if (pvVar3 != (void *)0x0) {
        FUN_004031ea(pvVar3,*(void **)this,*(int *)((int)this + 4));
        free(*(void **)this);
        *(void **)this = pvVar3;
        *(uint *)((int)this + 8) = uVar2;
        in_EAX = extraout_EAX;
        goto LAB_00404265;
      }
    }
    uVar1 = 0;
  }
  else {
LAB_00404265:
    uVar1 = CONCAT31((int3)((uint)in_EAX >> 8),1);
  }
  return uVar1;
}



/* === FUN_00404273 @ 00404273 === */

undefined4 __thiscall FUN_00404273(void *this,uint param_1)

{
  void *in_EAX;
  undefined4 uVar1;
  uint uVar2;
  void *pvVar3;
  void *extraout_EAX;
  
  if (*(uint *)((int)this + 8) < param_1) {
    uVar2 = *(uint *)((int)this + 0xc);
    if (*(int *)this == 0) {
      if (param_1 < uVar2) {
        param_1 = uVar2;
      }
      in_EAX = calloc(param_1,0x18);
      *(void **)this = in_EAX;
      if (in_EAX != (void *)0x0) {
        *(uint *)((int)this + 8) = param_1;
        goto LAB_00404302;
      }
    }
    else {
      if (uVar2 == 0) {
        uVar2 = *(uint *)((int)this + 4) >> 3;
        if (uVar2 < 4) {
          uVar2 = 4;
        }
        else if (0x400 < uVar2) {
          uVar2 = 0x400;
        }
      }
      uVar2 = uVar2 + *(uint *)((int)this + 8);
      if (uVar2 <= param_1) {
        uVar2 = param_1;
      }
      pvVar3 = calloc(uVar2,0x18);
      if (pvVar3 != (void *)0x0) {
        FUN_0040320e(pvVar3,*(void **)this,*(int *)((int)this + 4));
        free(*(void **)this);
        *(void **)this = pvVar3;
        *(uint *)((int)this + 8) = uVar2;
        in_EAX = extraout_EAX;
        goto LAB_00404302;
      }
    }
    uVar1 = 0;
  }
  else {
LAB_00404302:
    uVar1 = CONCAT31((int3)((uint)in_EAX >> 8),1);
  }
  return uVar1;
}



/* === FUN_00404310 @ 00404310 === */

void __fastcall FUN_00404310(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_004015bc;
  FUN_00403398((int)param_1);
  if (*(char *)(param_1 + 10) != '\0') {
    *(undefined1 *)(param_1 + 10) = 0;
    DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 4));
  }
  FUN_00403313(param_1 + 1);
  FUN_00402ff0(param_1 + 1);
  return;
}



/* === FUN_0040434c @ 0040434c === */

undefined4 FUN_0040434c(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0;
  }
  return 0x80004001;
}



/* === FUN_00404374 @ 00404374 === */

undefined4 * __thiscall FUN_00404374(void *this,byte param_1)

{
  FUN_00404310(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === FUN_0040439a @ 0040439a === */

undefined4 __fastcall FUN_0040439a(int param_1)

{
  undefined4 uVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  uVar1 = FUN_004040d5((void *)(param_1 + 4),(undefined4 *)&stack0x00000004);
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  return uVar1;
}



/* === FUN_004043cf @ 004043cf === */

void __fastcall FUN_004043cf(int *param_1,undefined4 param_2,LPCWSTR param_3,int *param_4)

{
  WCHAR WVar1;
  LPVOID pvVar2;
  int iVar3;
  LPCWSTR pWVar4;
  rsize_t rVar5;
  LPCWSTR pWVar6;
  LPWSTR pWVar7;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined1 local_58 [8];
  LPVOID local_50;
  undefined4 local_4c;
  wchar_t local_48 [32];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  if ((param_3 != (LPCWSTR)0x0) && (param_4 != (int *)0x0)) {
    *param_4 = 0;
    iVar3 = lstrlenW(param_3);
    FUN_00402ab6(local_58,iVar3 * 2);
    if (local_50 == (LPVOID)0x0) {
      CoTaskMemFree((LPVOID)0x0);
      param_2 = extraout_EDX;
    }
    else {
      *param_1 = (int)param_3;
      WVar1 = *param_3;
      local_4c = 0;
      pvVar2 = local_50;
      while (WVar1 != L'\0') {
        pWVar4 = (LPCWSTR)*param_1;
        local_50 = pvVar2;
        if (*pWVar4 == L'%') {
          pWVar4 = CharNextW(pWVar4);
          *param_1 = (int)pWVar4;
          if (*pWVar4 == L'%') goto LAB_004044b1;
          pWVar4 = FUN_00402c95(pWVar4,L'%');
          if (pWVar4 == (LPCWSTR)0x0) {
LAB_004044eb:
            local_4c = 0x80020009;
            goto LAB_004044dd;
          }
          rVar5 = (int)pWVar4 - *param_1 >> 1;
          if (0x1f < (int)rVar5) {
            local_4c = 0x80004005;
            goto LAB_004044dd;
          }
          FUN_00407da7(local_48,0x20,(wchar_t *)*param_1,rVar5);
          pWVar6 = (LPCWSTR)FUN_0040439a(param_1[1]);
          if (pWVar6 == (LPCWSTR)0x0) goto LAB_004044eb;
          iVar3 = FUN_00403357(local_58,pWVar6);
          if (iVar3 == 0) goto LAB_004044fd;
          pWVar6 = (LPCWSTR)*param_1;
          while (pWVar6 != pWVar4) {
            pWVar6 = CharNextW((LPCWSTR)*param_1);
            *param_1 = (int)pWVar6;
          }
        }
        else {
LAB_004044b1:
          iVar3 = FUN_00402af0(local_58,pWVar4,1);
          if (iVar3 == 0) {
LAB_004044fd:
            local_4c = 0x8007000e;
            goto LAB_004044dd;
          }
        }
        pWVar7 = CharNextW((LPCWSTR)*param_1);
        *param_1 = (int)pWVar7;
        pvVar2 = local_50;
        WVar1 = *pWVar7;
      }
      local_50 = (LPVOID)0x0;
      *param_4 = (int)pvVar2;
LAB_004044dd:
      CoTaskMemFree(local_50);
      param_2 = extraout_EDX_00;
    }
  }
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,param_2);
  return;
}



/* === FUN_00404521 @ 00404521 === */

void FUN_00404521(int param_1,uint param_2,undefined4 **param_3,uint param_4,int *param_5)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 **ppuVar5;
  undefined4 *local_8;
  
  iVar1 = param_1;
  local_8 = (undefined4 *)0x0;
  if (*(int *)(param_1 + 0x488) == 0) {
    FUN_00409a4f(param_1,param_2,(int *)param_3,param_4,param_5);
    return;
  }
  if (*(int *)(param_1 + 0x488) != 2) {
    puVar3 = (undefined4 *)FUN_00403145((void *)(param_1 + 0x4ac),0);
    ppuVar5 = param_3;
    goto LAB_00404654;
  }
  local_8 = LocalAlloc(0x40,0x14);
  ppuVar5 = param_3;
  if (local_8 == (undefined4 *)0x0) {
LAB_004045fb:
    piVar2 = (int *)0x8007000e;
LAB_00404600:
    if ((int)piVar2 < 0) {
      return;
    }
  }
  else {
    param_1 = 0;
    piVar2 = FUN_00403afe((void *)(iVar1 + -8),*(int **)(*param_5 + 0xc),(int *)(*param_3)[3],1,
                          &param_1);
    if (piVar2 != (int *)0x0) goto LAB_00404600;
    puVar3 = (undefined4 *)FUN_00403145((void *)(iVar1 + 0x4e0),0);
    piVar2 = (int *)*puVar3;
    (**(code **)(*piVar2 + 4))(piVar2);
    iVar4 = (**(code **)(*piVar2 + 0x14))(piVar2);
    param_3 = LocalAlloc(0x40,(uint)*(ushort *)(iVar4 + 2) * (*ppuVar5)[2] * 4);
    if (param_3 == (undefined4 **)0x0) goto LAB_004045fb;
    FUN_0040311b((void *)(iVar1 + 0x4f0),0,&param_3);
    *local_8 = **ppuVar5;
    local_8[1] = param_3;
    local_8[2] = (*ppuVar5)[2];
    local_8[3] = piVar2;
    local_8[4] = (*ppuVar5)[4];
  }
  puVar3 = (undefined4 *)FUN_00403145((void *)(iVar1 + 0x4ac),0);
  iVar4 = (**(code **)(*(int *)*puVar3 + 0xc))((int *)*puVar3,param_2,ppuVar5,param_4,&local_8);
  if (iVar4 < 0) {
    return;
  }
  puVar3 = (undefined4 *)FUN_00403145((void *)(iVar1 + 0x4ac),1);
  ppuVar5 = &local_8;
LAB_00404654:
  (**(code **)(*(int *)*puVar3 + 0xc))((int *)*puVar3,param_2,ppuVar5,param_4,param_5);
  return;
}



/* === FUN_0040467f @ 0040467f === */

void FUN_0040467f(IAudioMediaType *param_1,IAudioMediaType *param_2,IAudioMediaType **param_3,
                 int *param_4)

{
  if (*(int *)(param_1 + 0x490) == 0) {
    CBaseAudioProcessingObject::IsInputFormatSupported(param_1,param_2,param_3);
  }
  else {
    FUN_00403afe(param_1,(int *)param_2,(int *)param_3,0,param_4);
  }
  return;
}



/* === FUN_004046b7 @ 004046b7 === */

void FUN_004046b7(void *param_1,int *param_2,int *param_3,int *param_4)

{
  if (*(int *)((int)param_1 + 0x490) == 0) {
    FUN_0040a0c3(param_1,param_2,param_3,param_4);
  }
  else {
    FUN_00403ded(param_1,param_2,param_3,0,param_4);
  }
  return;
}



/* === FUN_004046ef @ 004046ef === */

undefined4 __thiscall FUN_004046ef(void *this,undefined4 *param_1,undefined4 *param_2)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = PTR_FUN_0040d070;
  iVar2 = (*(code *)PTR_FUN_0040d070)(*(undefined4 *)this,*(int *)((int)this + 8) + 1,4);
  if (iVar2 != 0) {
    *(int *)this = iVar2;
    iVar2 = (*(code *)puVar1)(*(undefined4 *)((int)this + 4),*(int *)((int)this + 8) + 1,4);
    if (iVar2 != 0) {
      *(int *)((int)this + 4) = iVar2;
      FUN_00404102(this,*(int *)((int)this + 8),param_1,param_2);
      *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
      return 1;
    }
  }
  return 0;
}



/* === FUN_0040474d @ 0040474d === */

void __thiscall FUN_0040474d(void *this,uint param_1)

{
  uint uVar1;
  
  uVar1 = FUN_004031c0(param_1,2);
  FUN_00404133(this,uVar1);
  return;
}



/* === FUN_00404771 @ 00404771 === */

void __thiscall FUN_00404771(void *this,uint param_1)

{
  uint uVar1;
  
  uVar1 = FUN_004031c0(param_1,2);
  FUN_0040415f(this,uVar1);
  return;
}



/* === FUN_00404795 @ 00404795 === */

void __thiscall FUN_00404795(void *this,uint param_1)

{
  uint uVar1;
  
  uVar1 = FUN_004031c0(param_1,1);
  FUN_0040415f(this,uVar1);
  return;
}



/* === FID_conflict:operator= @ 004047b9 === */

/* Library Function - Multiple Matches With Different Base Names
    public: struct IDispatch * __thiscall ATL::CComPtr<struct IDispatch>::operator=(struct IDispatch
   *)
    public: struct IHTMLDocument2 * __thiscall ATL::CComPtr<struct IHTMLDocument2>::operator=(struct
   IHTMLDocument2 *)
    public: struct IHTMLOptionButtonElement * __thiscall ATL::CComPtr<struct
   IHTMLOptionButtonElement>::operator=(struct IHTMLOptionButtonElement *)
    public: struct IHTMLOptionElement * __thiscall ATL::CComPtr<struct
   IHTMLOptionElement>::operator=(struct IHTMLOptionElement *)
     7 names - too many to list
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

void __thiscall FID_conflict_operator_(void *this,int *param_1)

{
  if (*(int **)this != param_1) {
    FUN_00402880(this,param_1);
  }
  return;
}



/* === FUN_004047d7 @ 004047d7 === */

undefined4 * __thiscall FUN_004047d7(void *this,byte param_1)

{
  FUN_0040418b(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === FUN_004047fd @ 004047fd === */

undefined4 * __fastcall FUN_004047fd(undefined4 *param_1)

{
  FUN_004041a6(param_1);
  *param_1 = &PTR_QueryInterface_004015d4;
  return param_1;
}



/* === _IsEqualGUIDAligned@8 @ 00404818 === */

/* Library Function - Single Match
    _IsEqualGUIDAligned@8
   
   Library: Visual Studio 2019 Release */

undefined4 _IsEqualGUIDAligned_8(int *param_1,int *param_2)

{
  undefined4 uVar1;
  
  if ((((*param_1 == *param_2) && (param_1[1] == param_2[1])) && (param_1[2] == param_2[2])) &&
     (param_1[3] == param_2[3])) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



/* === FUN_00404851 @ 00404851 === */

int FUN_00404851(int param_1,undefined4 *param_2,_GUID *param_3,undefined4 *param_4)

{
  code *pcVar1;
  int iVar2;
  int *piVar3;
  
  if ((param_1 == 0) || (param_2 == (undefined4 *)0x0)) {
    iVar2 = -0x7ff8ffa9;
  }
  else if (param_4 == (undefined4 *)0x0) {
    iVar2 = -0x7fffbffd;
  }
  else {
    *param_4 = 0;
    iVar2 = ATL::InlineIsEqualUnknown(param_3);
    if (iVar2 == 0) {
      for (; pcVar1 = (code *)param_2[2], pcVar1 != (code *)0x0; param_2 = param_2 + 3) {
        piVar3 = (int *)*param_2;
        if ((piVar3 == (int *)0x0) ||
           (iVar2 = _IsEqualGUIDAligned_8(piVar3,(int *)param_3), iVar2 != 0)) {
          if (pcVar1 == (code *)0x1) goto LAB_00404887;
          iVar2 = (*pcVar1)(param_1,param_3,param_4,param_2[1]);
          if (iVar2 == 0) {
            return 0;
          }
          if ((piVar3 != (int *)0x0) && (iVar2 < 0)) {
            return iVar2;
          }
        }
      }
      iVar2 = -0x7fffbffe;
    }
    else {
LAB_00404887:
      piVar3 = (int *)(param_2[1] + param_1);
      (**(code **)(*piVar3 + 4))(piVar3);
      *param_4 = piVar3;
      iVar2 = 0;
    }
  }
  return iVar2;
}



/* === FUN_004048f7 @ 004048f7 === */

LONG FUN_004048f7(int param_1)

{
  LONG LVar1;
  
  LVar1 = InterlockedIncrement((LONG *)(param_1 + 4));
  if (LVar1 == 2) {
    (**(code **)(*DAT_0040d09c + 4))();
  }
  return LVar1;
}



/* === _InternalQueryInterface @ 00404928 === */

/* Library Function - Single Match
    public: long __thiscall ATL::CAccessibleProxy::_InternalQueryInterface(struct _GUID const &,void
   * *)
   
   Library: Visual Studio 2008 Release */

long __thiscall
ATL::CAccessibleProxy::_InternalQueryInterface(CAccessibleProxy *this,_GUID *param_1,void **param_2)

{
  int iVar1;
  
  iVar1 = FUN_00404851((int)this,&PTR_DAT_004015e8,param_1,param_2);
  return iVar1;
}



/* === QueryInterface @ 00404947 === */

/* Library Function - Single Match
    public: virtual long __stdcall CMFCComObject<class ATL::CAccessibleProxy>::QueryInterface(struct
   _GUID const &,void * *)
   
   Library: Visual Studio 2008 Release */

long CMFCComObject<ATL::CAccessibleProxy>::QueryInterface(_GUID *param_1,void **param_2)

{
  long lVar1;
  void **in_stack_0000000c;
  
  lVar1 = ATL::CAccessibleProxy::_InternalQueryInterface
                    ((CAccessibleProxy *)param_1,(_GUID *)param_2,in_stack_0000000c);
  return lVar1;
}



/* === FUN_00404963 @ 00404963 === */

LONG FUN_00404963(void *param_1)

{
  LONG LVar1;
  
  LVar1 = InterlockedDecrement((LONG *)((int)param_1 + 4));
  if (LVar1 == 0) {
    if (param_1 != (void *)0x0) {
      FUN_004047d7(param_1,1);
    }
  }
  else if (LVar1 == 1) {
    (**(code **)(*DAT_0040d09c + 8))();
  }
  return LVar1;
}



/* === FUN_004049a9 @ 004049a9 === */

undefined4 __thiscall FUN_004049a9(void *this,uint param_1,int param_2)

{
  int extraout_EAX;
  
  if (param_2 != -1) {
    *(int *)((int)this + 0xc) = param_2;
  }
  if (param_1 == 0) {
    param_2 = 0;
    if (*(void **)this != (void *)0x0) {
      free(*(void **)this);
      *(undefined4 *)this = 0;
      param_2 = extraout_EAX;
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 8) = 0;
  }
  else {
    if ((*(uint *)((int)this + 8) < param_1) &&
       (param_2 = FUN_004041d6(this,param_1), (char)param_2 == '\0')) {
      return param_2;
    }
    *(uint *)((int)this + 4) = param_1;
  }
  return CONCAT31((int3)((uint)param_2 >> 8),1);
}



/* === FUN_004049fd @ 004049fd === */

undefined4 __thiscall FUN_004049fd(void *this,uint param_1,int param_2)

{
  int extraout_EAX;
  
  if (param_2 != -1) {
    *(int *)((int)this + 0xc) = param_2;
  }
  if (param_1 == 0) {
    param_2 = 0;
    if (*(void **)this != (void *)0x0) {
      free(*(void **)this);
      *(undefined4 *)this = 0;
      param_2 = extraout_EAX;
    }
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 8) = 0;
  }
  else {
    if ((*(uint *)((int)this + 8) < param_1) &&
       (param_2 = FUN_00404273(this,param_1), (char)param_2 == '\0')) {
      return param_2;
    }
    *(uint *)((int)this + 4) = param_1;
  }
  return CONCAT31((int3)((uint)param_2 >> 8),1);
}



/* === FUN_00404a51 @ 00404a51 === */

bool __thiscall FUN_00404a51(void *this,LPCWSTR param_1,LPCWSTR param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  void *local_18;
  void *local_14;
  HLOCAL local_10;
  void *local_c;
  int local_8;
  
  if ((param_1 == (LPCWSTR)0x0) || (param_2 == (LPCWSTR)0x0)) {
    return false;
  }
  local_8 = 0;
  iVar3 = lstrlenW(param_1);
  uVar1 = iVar3 * 2 + 2;
  pvVar4 = (void *)FUN_00402f11(-(uint)((int)((ulonglong)uVar1 * 2 >> 0x20) != 0) |
                                (uint)((ulonglong)uVar1 * 2));
  local_18 = pvVar4;
  local_14 = pvVar4;
  iVar3 = lstrlenW(param_2);
  uVar2 = iVar3 * 2 + 2;
  local_10 = (HLOCAL)FUN_00402f11(-(uint)((int)((ulonglong)uVar2 * 2 >> 0x20) != 0) |
                                  (uint)((ulonglong)uVar2 * 2));
  local_c = local_10;
  if ((pvVar4 != (void *)0x0) && (local_10 != (HLOCAL)0x0)) {
    FUN_0040277b(pvVar4,uVar1,param_1,uVar1);
    FUN_0040277b(local_c,uVar2,param_2,uVar2);
    iVar3 = FUN_004046ef(this,&local_18,&local_c);
    if (iVar3 != 0) {
      local_14 = (void *)0x0;
      local_10 = (HLOCAL)0x0;
      goto LAB_00404b12;
    }
  }
  local_8 = -0x7ff8fff2;
LAB_00404b12:
  FUN_00402f2f(local_10);
  FUN_00402f2f(local_14);
  return -1 < local_8;
}



/* === FUN_00404b3c @ 00404b3c === */

int FUN_00404b3c(int param_1,LPCWSTR param_2,LPCWSTR param_3)

{
  LPCRITICAL_SECTION lpCriticalSection;
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  
  iVar2 = param_1;
  if ((param_2 == (LPCWSTR)0x0) || (param_3 == (LPCWSTR)0x0)) {
    iVar2 = -0x7ff8ffa9;
  }
  else {
    lpCriticalSection = (LPCRITICAL_SECTION)(param_1 + 0x10);
    EnterCriticalSection(lpCriticalSection);
    param_1 = 0;
    bVar1 = FUN_00404a51((void *)(iVar2 + 4),param_2,param_3);
    LeaveCriticalSection(lpCriticalSection);
    FUN_00402fd1(&param_1);
    iVar2 = (-(uint)(CONCAT31(extraout_var,bVar1) != 0) & 0x7ff8fff2) + 0x8007000e;
  }
  return iVar2;
}



/* === FUN_00404ba1 @ 00404ba1 === */

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void __thiscall FUN_00404ba1(void *this,undefined4 *param_1,LPCWSTR param_2,WCHAR *param_3)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  LPWSTR lpsz;
  LPCWSTR lpsz_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined4 uVar4;
  WCHAR *pWVar5;
  uint uVar6;
  undefined4 *local_2118;
  LPCWSTR local_2114;
  uint local_2110;
  WCHAR *local_210c;
  WCHAR local_2108 [128];
  WCHAR local_2008 [4096];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  uVar6 = 0;
  local_2118 = param_1;
  local_2114 = param_2;
  local_2110 = 0;
  iVar2 = FUN_00402d21(this,local_2008);
  uVar4 = extraout_EDX;
  if ((iVar2 < 0) ||
     (iVar2 = FUN_00402b82(local_2008,(undefined2 *)&local_2110), uVar4 = extraout_EDX_00,
     iVar2 == 0)) goto LAB_00404e7d;
  FUN_00402cf8(this);
  iVar2 = FUN_00402d21(this,local_2008);
  uVar4 = extraout_EDX_01;
  if (iVar2 < 0) goto LAB_00404e7d;
  uVar3 = local_2110 & 0xffff;
  if (uVar3 == 8) {
    uVar6 = FUN_004029e2(param_1,param_2,local_2008,1);
LAB_00404e5a:
    if (uVar6 != 0) {
      FUN_00402861(uVar6);
      uVar4 = extraout_EDX_05;
      goto LAB_00404e7d;
    }
  }
  else {
    if (uVar3 == 0x11) {
      local_2110 = lstrlenW(local_2008);
      uVar4 = extraout_EDX_02;
      if ((local_2110 & 1) != 0) goto LAB_00404e7d;
      uVar3 = (int)local_2110 / 2;
      local_210c = (WCHAR *)0x0;
      FUN_00404795(&local_210c,uVar3);
      if (local_210c == (WCHAR *)0x0) {
        uVar4 = extraout_EDX_03;
        if (&stack0x00000000 != (undefined1 *)0x2108) {
          FUN_004030e4(&local_210c);
          uVar4 = extraout_EDX_04;
        }
        goto LAB_00404e7d;
      }
      memset(local_210c,0,uVar3);
      if (0 < (int)local_2110) {
        do {
          pbVar1 = (byte *)((int)uVar6 / 2 + (int)local_210c);
          iVar2 = FUN_00402c1f(local_2008[uVar6]);
          *pbVar1 = *pbVar1 | (char)iVar2 << (4U - (char)((uVar6 & 1) << 2) & 0x1f);
          uVar6 = uVar6 + 1;
          param_1 = local_2118;
        } while ((int)uVar6 < (int)local_2110);
      }
      uVar6 = RegSetValueExW((HKEY)*param_1,local_2114,0,3,(BYTE *)local_210c,uVar3);
      if (local_210c != local_2108) {
        FUN_004030e4(&local_210c);
      }
      goto LAB_00404e5a;
    }
    if (uVar3 == 0x13) {
      local_2118 = (undefined4 *)0x0;
      Ordinal_277(local_2008,0,0,&local_2114);
      uVar6 = SetDWORDValue(param_1,param_2);
      FUN_00402fd1((int *)&local_2118);
      goto LAB_00404e5a;
    }
    if (uVar3 == 0x4008) {
      iVar2 = lstrlenW(local_2008);
      local_210c = (WCHAR *)0x0;
      FUN_00404771(&local_210c,iVar2 + 2);
      if (local_210c == (WCHAR *)0x0) {
        uVar6 = 0xe;
      }
      else {
        lpsz_00 = local_2008;
        pWVar5 = local_210c;
        while (local_2008[0] != L'\0') {
          lpsz = CharNextW(lpsz_00);
          if ((*lpsz_00 == L'\\') && (*lpsz == L'0')) {
            *pWVar5 = L'\0';
            lpsz_00 = CharNextW(lpsz);
          }
          else {
            *pWVar5 = *lpsz_00;
            lpsz_00 = lpsz_00 + 1;
          }
          pWVar5 = pWVar5 + 1;
          local_2008[0] = *lpsz_00;
        }
        *pWVar5 = L'\0';
        pWVar5[1] = L'\0';
        uVar6 = FUN_00402a25(local_2118,local_2114,local_210c);
      }
      if (local_210c != local_2108) {
        FUN_004030e4(&local_210c);
      }
      goto LAB_00404e5a;
    }
  }
  FUN_00402d21(this,param_3);
  uVar4 = extraout_EDX_06;
LAB_00404e7d:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar4);
  return;
}



/* === FUN_00404e93 @ 00404e93 === */

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void __thiscall FUN_00404e93(void *this,LPCWSTR param_1,HKEY param_2,int param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  LPCWSTR pWVar4;
  uint uVar5;
  errno_t eVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar7;
  CRegKey *this_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar8;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  HKEY local_2220;
  HKEY local_221c;
  HKEY local_2218;
  undefined4 *local_2214;
  WCHAR local_2210 [4096];
  wchar_t local_210 [260];
  uint local_8;
  
  iVar1 = param_4;
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_221c = (HKEY)0x0;
  local_2214 = this;
LAB_0040538a:
  iVar7 = FUN_00402d21(local_2214,param_1);
  do {
    if (iVar7 < 0) {
LAB_004053fe:
      ATL::CRegKey::Close((CRegKey *)&local_221c);
      uVar8 = extraout_EDX_04;
LAB_0040540b:
      FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar8);
      return;
    }
LAB_00405396:
    if (*param_1 == L'}') goto LAB_004053fe;
    local_2220 = (HKEY)0x1;
    iVar7 = lstrcmpiW(param_1,L"Delete");
    iVar3 = lstrcmpiW(param_1,L"ForceRemove");
    if ((iVar3 == 0) || (iVar7 == 0)) {
      iVar3 = FUN_00402d21(local_2214,param_1);
      if (iVar3 < 0) goto LAB_004053fe;
      if (param_3 == 0) goto LAB_00404fba;
      local_2218 = (HKEY)0x0;
      pWVar4 = FUN_00402c95(param_1,L'\\');
      if (pWVar4 == (LPCWSTR)0x0) {
        iVar3 = FUN_00402e2b(param_1);
        if (iVar3 != 0) {
          local_2218 = param_2;
          FUN_00403232(&local_2218,param_1);
          local_2218 = (HKEY)0x0;
        }
        if (iVar7 != 0) {
          ATL::CRegKey::Close((CRegKey *)&local_2218);
          goto LAB_00404fba;
        }
        iVar7 = FUN_00402d21(local_2214,param_1);
        if (-1 < iVar7) {
          iVar7 = FUN_00402e9d(local_2214,extraout_EDX,param_1);
          ATL::CRegKey::Close((CRegKey *)&local_2218);
LAB_00404fa4:
          if (-1 < iVar7) goto LAB_0040534f;
          goto LAB_004053fe;
        }
        this_00 = (CRegKey *)&local_2218;
        goto LAB_004053f9;
      }
      ATL::CRegKey::Close((CRegKey *)&local_2218);
      goto LAB_004053fe;
    }
LAB_00404fba:
    iVar7 = lstrcmpiW(param_1,L"NoRemove");
    if (iVar7 == 0) {
      local_2220 = (HKEY)0x0;
      iVar7 = FUN_00402d21(local_2214,param_1);
      if (iVar7 < 0) goto LAB_004053fe;
    }
    iVar7 = lstrcmpiW(param_1,L"Val");
    if (iVar7 != 0) {
      pWVar4 = FUN_00402c95(param_1,L'\\');
      if (pWVar4 == (LPCWSTR)0x0) {
        if (param_3 == 0) {
          if (iVar1 == 0) {
            uVar5 = FUN_00402983(&local_221c,param_2,param_1,0x20019);
          }
          else {
            uVar5 = 2;
          }
          param_4 = iVar1;
          if (uVar5 != 0) {
            param_4 = 1;
          }
          eVar6 = wcsncpy_s(local_210,0x104,param_1,0xffffffff);
          FUN_0040273a(eVar6);
          iVar7 = FUN_00402d21(local_2214,param_1);
          if (((-1 < iVar7) &&
              (iVar7 = FUN_00402e9d(local_2214,extraout_EDX_02,param_1), -1 < iVar7)) &&
             (((*param_1 != L'{' || (iVar7 = lstrlenW(param_1), iVar7 != 1)) ||
              (((iVar7 = FUN_00404e93(local_2214,param_1,local_221c,0,param_4), -1 < iVar7 ||
                (param_4 != 0)) && (iVar7 = FUN_00402d21(local_2214,param_1), -1 < iVar7))))))
          break;
        }
        else {
          iVar7 = FUN_00402983(&local_221c,param_2,param_1,0x2001f);
          if (((iVar7 != 0) &&
              (iVar7 = FUN_00402983(&local_221c,param_2,param_1,0x20019), iVar7 != 0)) &&
             (uVar5 = Create(&local_221c,param_2,param_1,(LPWSTR)0x0,0,0x2001f,
                             (LPSECURITY_ATTRIBUTES)0x0,(undefined4 *)0x0), uVar5 != 0)) {
            ATL::CRegKey::Close((CRegKey *)&local_221c);
            goto LAB_004053d6;
          }
          iVar7 = FUN_00402d21(local_2214,param_1);
          if (-1 < iVar7) {
            if (*param_1 == L'=') {
              iVar7 = FUN_00404ba1(local_2214,&local_221c,(LPCWSTR)0x0,param_1);
              goto LAB_00404fa4;
            }
            goto LAB_0040534f;
          }
        }
      }
      goto LAB_004053fe;
    }
    iVar7 = FUN_00402d21(local_2214,local_2210);
    if (((iVar7 < 0) || (iVar7 = FUN_00402d21(local_2214,param_1), iVar7 < 0)) || (*param_1 != L'=')
       ) goto LAB_004053fe;
    if (param_3 != 0) {
      local_2220 = param_2;
      iVar7 = FUN_00404ba1(local_2214,&local_2220,local_2210,param_1);
      local_2220 = (HKEY)0x0;
      ATL::CRegKey::Close((CRegKey *)&local_2220);
      goto LAB_00404fa4;
    }
    uVar8 = extraout_EDX_00;
    if ((iVar1 == 0) && (local_2220 != (HKEY)0x0)) {
      local_2218 = (HKEY)0x0;
      uVar5 = FUN_00402983(&local_2218,param_2,(LPCWSTR)0x0,0x20006);
      if ((uVar5 != 0) ||
         ((uVar5 = RegDeleteValueW(local_2218,local_2210), uVar5 != 0 && (uVar5 != 2)))) {
        FUN_00402861(uVar5);
        this_00 = (CRegKey *)&local_2218;
LAB_004053f9:
        ATL::CRegKey::Close(this_00);
        goto LAB_004053fe;
      }
      ATL::CRegKey::Close((CRegKey *)&local_2218);
      uVar8 = extraout_EDX_01;
    }
    iVar7 = FUN_00402e9d(local_2214,uVar8,param_1);
  } while( true );
  if (uVar5 != 2) {
    if (uVar5 == 0) {
      if ((iVar1 == 0) || (bVar2 = FUN_00402e61(local_221c), CONCAT31(extraout_var,bVar2) == 0)) {
        bVar2 = FUN_00402e61(local_221c);
        local_2218 = (HKEY)CONCAT31(extraout_var_00,bVar2);
        uVar5 = ATL::CRegKey::Close((CRegKey *)&local_221c);
        if (uVar5 != 0) {
          ATL::CRegKey::Close((CRegKey *)&local_221c);
LAB_004053d6:
          FUN_00402861(uVar5);
          uVar8 = extraout_EDX_03;
          goto LAB_0040540b;
        }
        if ((local_2220 != (HKEY)0x0) && (local_2218 == (HKEY)0x0)) {
          uVar5 = RegDeleteKeyW(param_2,local_210);
          local_2220 = (HKEY)0x0;
          if (uVar5 != 0) {
            FUN_00402861(uVar5);
            this_00 = (CRegKey *)&local_2220;
            goto LAB_004053f9;
          }
          ATL::CRegKey::Close((CRegKey *)&local_2220);
LAB_0040534f:
          if (((param_3 != 0) && (*param_1 == L'{')) && (iVar7 = lstrlenW(param_1), iVar7 == 1)) {
            iVar7 = FUN_00404e93(local_2214,param_1,local_221c,param_3,0);
            if (-1 < iVar7) goto LAB_0040538a;
            goto LAB_004053fe;
          }
        }
      }
      else {
        iVar7 = FUN_00402e2b(local_210);
        if ((iVar7 != 0) && (local_2220 != (HKEY)0x0)) {
          FUN_00403232(&local_221c,local_210);
        }
      }
    }
    else if (iVar1 == 0) {
      FUN_00402861(uVar5);
      goto LAB_004053fe;
    }
  }
  goto LAB_00405396;
}



/* === FUN_00405421 @ 00405421 === */

undefined4 * __fastcall FUN_00405421(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  *param_1 = &PTR_FUN_004015bc;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  puVar2 = param_1 + 4;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)(param_1 + 10) = 0;
  return param_1;
}



/* === FUN_00405452 @ 00405452 === */

undefined4 * __thiscall FUN_00405452(void *this,undefined4 param_1,undefined4 param_2)

{
  FUN_00402f4a((undefined4 *)((int)this + 0x44));
  FUN_0040a0f8(this,param_1);
  *(undefined ***)this = &PTR_LAB_00401610;
  *(undefined ***)((int)this + 4) = &PTR_LAB_004016e4;
  *(undefined ***)((int)this + 8) = &PTR_LAB_00401688;
  *(undefined ***)((int)this + 0x3c) = &PTR_LAB_00401678;
  *(undefined ***)((int)this + 0x40) = &PTR_LAB_0040166c;
  *(undefined4 *)((int)this + 0x48c) = 0;
  *(undefined4 *)((int)this + 0x494) = 0;
  *(undefined4 *)((int)this + 0x498) = 0;
  *(undefined4 *)((int)this + 0x49c) = 0;
  *(undefined4 *)((int)this + 0x4a0) = 0;
  *(undefined4 *)((int)this + 0x4a4) = 0;
  *(undefined4 *)((int)this + 0x4a8) = 0;
  *(undefined4 *)((int)this + 0x4ac) = 0;
  *(undefined4 *)((int)this + 0x4b0) = 0;
  *(undefined4 *)((int)this + 0x4b4) = 0;
  *(undefined4 *)((int)this + 0x4b8) = 0;
  *(undefined4 *)((int)this + 0x4bc) = 0;
  *(undefined4 *)((int)this + 0x4c0) = 0;
  *(undefined4 *)((int)this + 0x4c4) = 0;
  *(undefined4 *)((int)this + 0x4c8) = 0;
  *(undefined4 *)((int)this + 0x4cc) = 0;
  *(undefined4 *)((int)this + 0x4d0) = 0;
  *(undefined4 *)((int)this + 0x4d4) = 0;
  *(undefined4 *)((int)this + 0x4d8) = 0;
  *(undefined4 *)((int)this + 0x4dc) = 0;
  *(undefined4 *)((int)this + 0x4e0) = 0;
  *(undefined4 *)((int)this + 0x4e8) = 0;
  *(undefined4 *)((int)this + 0x4ec) = 0;
  *(undefined4 *)((int)this + 0x4f0) = 0;
  *(undefined4 *)((int)this + 0x4f4) = 0;
  *(undefined4 *)((int)this + 0x4f8) = 0;
  *(undefined4 *)((int)this + 0x4fc) = 0;
  *(undefined4 *)((int)this + 0x500) = 0;
  *(undefined4 *)((int)this + 0x504) = 0;
  *(undefined4 *)((int)this + 100) = param_2;
  FID_conflict_operator_((undefined4 *)((int)this + 0x48c),(int *)0x0);
  *(undefined4 *)((int)this + 0x490) = 0;
  *(undefined4 *)((int)this + 0x68) = 0;
  *(undefined4 *)((int)this + 0x4e4) = 0;
  return this;
}



/* === FUN_00405538 @ 00405538 === */

void __fastcall FUN_00405538(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  uVar3 = 0;
  *param_1 = &PTR_LAB_00401610;
  param_1[1] = &PTR_LAB_004016e4;
  param_1[2] = &PTR_LAB_00401688;
  param_1[0xf] = &PTR_LAB_00401678;
  param_1[0x10] = &PTR_LAB_0040166c;
  if (param_1[0x124] != 0) {
    do {
      piVar1 = (int *)FUN_00403145(param_1 + 0x12d,uVar3);
      piVar1 = (int *)*piVar1;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
      }
      piVar1 = (int *)FUN_00403145(param_1 + 0x125,uVar3);
      piVar1 = (int *)*piVar1;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
      }
      piVar1 = (int *)FUN_00403145(param_1 + 0x129,uVar3);
      piVar1 = (int *)*piVar1;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
      }
      piVar1 = (int *)FUN_00403145(param_1 + 0x13a,uVar3);
      piVar1 = (int *)*piVar1;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
      }
      puVar2 = (undefined4 *)FUN_00403145(param_1 + 0x13e,uVar3);
      if ((HLOCAL)*puVar2 != (HLOCAL)0x0) {
        LocalFree((HLOCAL)*puVar2);
      }
      piVar1 = (int *)FUN_00403145(param_1 + 0x131,uVar3);
      piVar1 = (int *)*piVar1;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < (uint)param_1[0x124]);
  }
  piVar1 = (int *)param_1[0x139];
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    param_1[0x139] = 0;
  }
  FUN_004049a9(param_1 + 0x12d,0,-1);
  FUN_004049a9(param_1 + 0x125,0,-1);
  FUN_004049a9(param_1 + 0x129,0,-1);
  FUN_004049a9(param_1 + 0x131,0,-1);
  FUN_004049fd(param_1 + 0x135,0,-1);
  FUN_004049a9(param_1 + 0x13a,0,-1);
  FUN_004049a9(param_1 + 0x13e,0,-1);
  FUN_004041c2(param_1 + 0x13e);
  FUN_004041c2(param_1 + 0x13a);
  FUN_004041c2(param_1 + 0x135);
  FUN_004041c2(param_1 + 0x131);
  FUN_004041c2(param_1 + 0x12d);
  FUN_004041c2(param_1 + 0x129);
  FUN_004041c2(param_1 + 0x125);
  piVar1 = (int *)param_1[0x123];
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  FUN_00409eab((int)param_1);
  FUN_00403087((int)(param_1 + 0x11));
  return;
}



/* === FUN_004056f5 @ 004056f5 === */

void __thiscall FUN_004056f5(void *this,uint param_1)

{
  short sVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  short *psVar5;
  PROPERTYKEY *pkey;
  HRESULT HVar6;
  int iVar7;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  uint uVar8;
  short local_128 [4];
  short *local_120;
  undefined4 uStack_11c;
  short local_118 [4];
  int local_110;
  undefined4 uStack_10c;
  int local_108;
  void *local_104;
  uint local_100;
  undefined4 local_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  uint local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  WCHAR local_d0;
  undefined1 local_ce [198];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_108 = -0x7fffbffb;
  local_d0 = L'\0';
  memset(local_ce,0,0xc6);
  local_e8 = 0;
  local_e4 = 0;
  uStack_e0 = 0;
  uStack_dc = 0;
  local_d8 = 0;
  local_104 = (void *)((int)this + 0x4d4);
  local_d4 = 0;
  uVar3 = FUN_004049fd(local_104,param_1,-1);
  if ((((char)uVar3 != '\0') && (*(int *)((int)this + 0x4e4) != 0)) && (local_100 = 0, param_1 != 0)
     ) {
    local_d4 = 0xffffffff;
    local_d8 = 0;
    do {
      local_e8 = DAT_00401644;
      local_e4 = DAT_00401648;
      uStack_e0 = DAT_0040164c;
      uStack_dc = DAT_00401650;
      FUN_0040316a(local_104,local_100,&local_e8);
      uVar8 = local_100;
      local_fc = DAT_004013c8;
      uStack_f8 = DAT_004013cc;
      uStack_f4 = DAT_004013d0;
      uStack_f0 = DAT_004013d4;
      local_128[0] = 0;
      local_128[1] = 0;
      local_128[2] = 0;
      local_128[3] = 0;
      local_120 = (short *)0x0;
      uStack_11c = 0;
      local_ec = local_100;
      iVar4 = (**(code **)(**(int **)((int)this + 0x4e4) + 0x14))
                        (*(int **)((int)this + 0x4e4),&local_fc,local_128);
      if ((-1 < iVar4) && (local_128[0] == 0x1f)) {
        psVar5 = local_120;
        do {
          sVar1 = *psVar5;
          *(short *)(local_ce + (-2 - (int)local_120) + (int)psVar5) = sVar1;
          psVar5 = psVar5 + 1;
        } while (sVar1 != 0);
        pkey = (PROPERTYKEY *)FUN_0040319b(local_104,uVar8);
        HVar6 = PSPropertyKeyFromString(&local_d0,pkey);
        if (-1 < HVar6) {
          piVar2 = *(int **)((int)this + 0x4e4);
          local_118[0] = 0;
          local_118[1] = 0;
          local_118[2] = 0;
          local_118[3] = 0;
          local_110 = 0;
          uStack_10c = 0;
          iVar4 = *piVar2;
          psVar5 = local_118;
          iVar7 = FUN_0040319b(local_104,local_100);
          iVar4 = (**(code **)(iVar4 + 0x14))(piVar2,iVar7,psVar5);
          if (-1 < iVar4) {
            if (local_118[0] == 0x13) {
              if (((local_110 == -1) || (local_110 == 0)) || (local_110 == 1)) {
                iVar4 = FUN_0040319b(local_104,local_100);
                *(int *)(iVar4 + 0x14) = local_110;
              }
            }
            else if ((local_118[0] == 0xb) && (((short)local_110 == 0 || ((short)local_110 == 1))))
            {
              iVar7 = (int)(short)local_110;
              iVar4 = FUN_0040319b(local_104,local_100);
              *(int *)(iVar4 + 0x14) = iVar7;
            }
          }
          PropVariantClear((PROPVARIANT *)local_118);
          local_108 = 0;
          uVar8 = local_100;
        }
      }
      PropVariantClear((PROPVARIANT *)local_128);
      local_100 = uVar8 + 1;
    } while (local_100 < param_1);
    uVar3 = extraout_EDX;
    if (-1 < local_108) goto LAB_0040594b;
  }
  FUN_004049fd(local_104,0,-1);
  uVar3 = extraout_EDX_00;
LAB_0040594b:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar3);
  return;
}



/* === FUN_00405967 @ 00405967 === */

int FUN_00405967(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *this;
  
  this = (undefined4 *)0x0;
  if (param_3 == (undefined4 *)0x0) {
    iVar1 = -0x7fffbffd;
  }
  else {
    *param_3 = 0;
    iVar1 = -0x7ff8fff2;
    puVar2 = LocalAlloc(0x40,0x28);
    if (puVar2 != (undefined4 *)0x0) {
      this = FUN_004047fd(puVar2);
    }
    if (this != (undefined4 *)0x0) {
      this[9] = param_1;
      iVar1 = FUN_0040282e((CComCriticalSection *)(this + 2));
      if ((iVar1 < 0) || (iVar1 = (**(code **)*this)(this,param_2,param_3), iVar1 != 0)) {
        FUN_004047d7(this,1);
      }
    }
  }
  return iVar1;
}



/* === FUN_004059e4 @ 004059e4 === */

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void __fastcall FUN_004059e4(int *param_1,undefined4 param_2,LPCWSTR param_3,int param_4)

{
  int iVar1;
  HKEY pHVar2;
  int iVar3;
  short *psVar4;
  undefined4 extraout_EDX;
  undefined4 uVar5;
  undefined8 uVar6;
  short *local_200c;
  WCHAR local_2008 [4096];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_200c = (short *)0x0;
  uVar6 = FUN_004043cf(param_1,param_2,param_3,(int *)&local_200c);
  uVar5 = (undefined4)((ulonglong)uVar6 >> 0x20);
  if ((int)uVar6 < 0) {
LAB_00405ade:
    FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar5);
    return;
  }
  *param_1 = (int)local_200c;
  psVar4 = local_200c;
LAB_00405b11:
  if ((((*psVar4 == 0) || (iVar1 = FUN_00402d21(param_1,local_2008), iVar1 < 0)) ||
      (pHVar2 = (HKEY)FUN_00402c5e(local_2008), pHVar2 == (HKEY)0x0)) ||
     ((iVar1 = FUN_00402d21(param_1,local_2008), iVar1 < 0 || (local_2008[0] != L'{'))))
  goto LAB_00405ad0;
  if (param_4 == 0) {
    iVar1 = FUN_00404e93(param_1,local_2008,pHVar2,0,0);
    if (iVar1 < 0) goto LAB_00405ad0;
  }
  else {
    iVar1 = *param_1;
    iVar3 = FUN_00404e93(param_1,local_2008,pHVar2,param_4,0);
    if (iVar3 < 0) {
      *param_1 = iVar1;
      FUN_00404e93(param_1,local_2008,pHVar2,0,0);
LAB_00405ad0:
      CoTaskMemFree(local_200c);
      uVar5 = extraout_EDX;
      goto LAB_00405ade;
    }
  }
  FUN_00402cf8(param_1);
  psVar4 = (short *)*param_1;
  goto LAB_00405b11;
}



/* === FUN_00405b28 @ 00405b28 === */

undefined4 * __fastcall FUN_00405b28(undefined4 *param_1)

{
  FUN_00405452(param_1,&DAT_0040e000,1);
  *param_1 = &PTR_LAB_0040169c;
  param_1[1] = &PTR_LAB_004016e4;
  param_1[2] = &PTR_LAB_00401688;
  param_1[0xf] = &PTR_LAB_00401678;
  param_1[0x10] = &PTR_LAB_0040166c;
  param_1[0x142] = &PTR_LAB_00401654;
  param_1[0x143] = &PTR_LAB_0040166c;
  return param_1;
}



/* === FUN_00405b78 @ 00405b78 === */

undefined4 * __fastcall FUN_00405b78(undefined4 *param_1)

{
  FUN_00405452(param_1,&DAT_0040e448,0);
  *param_1 = &PTR_LAB_004016fc;
  param_1[1] = &PTR_LAB_004016e4;
  param_1[2] = &PTR_LAB_004016d0;
  param_1[0xf] = &PTR_LAB_00401678;
  param_1[0x10] = &PTR_LAB_0040166c;
  param_1[0x142] = &PTR_LAB_0040166c;
  return param_1;
}



/* === FUN_00405bbe @ 00405bbe === */

undefined4 * __thiscall FUN_00405bbe(void *this,byte param_1)

{
  FUN_004074fb(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === FUN_00405be4 @ 00405be4 === */

undefined4 * __thiscall FUN_00405be4(void *this,byte param_1)

{
  FUN_00405538(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === FUN_00405c0a @ 00405c0a === */

void __fastcall
FUN_00405c0a(undefined4 param_1,undefined4 param_2,void *param_3,int param_4,int param_5)

{
  wchar_t *pwVar1;
  uint uVar2;
  HRESULT HVar3;
  int iVar4;
  int **ppiVar5;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *puVar6;
  ulong *puVar7;
  int *piVar8;
  short local_c8 [4];
  wchar_t *local_c0;
  undefined4 uStack_bc;
  uint local_b8;
  int *local_b4;
  int *local_b0;
  int *local_ac;
  int *local_a8;
  int *local_a4;
  int *local_a0;
  int *local_9c;
  uint local_98;
  uint local_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  int local_80;
  IID local_7c;
  char local_6c [100];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_9c = (int *)0x0;
  local_ac = (int *)0x0;
  local_a0 = (int *)0x0;
  local_a8 = (int *)0x0;
  local_b0 = (int *)0x0;
  local_98 = 0;
  if (param_5 != 0) {
    if (param_4 == 0) {
      local_94 = -0x7fffbffd;
      goto LAB_0040613c;
    }
    if (param_4 == 0x24) {
      piVar8 = *(int **)(param_5 + 0x18);
      *(int **)((int)param_3 + 0x4e4) = piVar8;
      local_b4 = piVar8;
      (**(code **)(*piVar8 + 4))(piVar8);
      if (piVar8 == (int *)0x0) {
        *(undefined4 *)((int)param_3 + 0x490) = 0;
        local_94 = 0;
        param_2 = extraout_EDX;
        goto LAB_0040613c;
      }
      (**(code **)(*piVar8 + 4))(piVar8);
      local_c8[0] = 0;
      local_c8[1] = 0;
      local_c8[2] = 0;
      local_c8[3] = 0;
      local_c0 = (wchar_t *)0x0;
      uStack_bc = 0;
      local_94 = (**(code **)(*piVar8 + 0x14))(piVar8,&DAT_004013b4,local_c8);
      pwVar1 = local_c0;
      if (((int)local_94 < 0) || (local_c8[0] != 0x13)) {
        *(undefined4 *)((int)param_3 + 0x490) = 0;
        local_94 = 0;
        PropVariantClear((PROPVARIANT *)local_c8);
      }
      else {
        PropVariantClear((PROPVARIANT *)local_c8);
        if (pwVar1 == (wchar_t *)0x0) {
          *(undefined4 *)((int)param_3 + 0x490) = 0;
          local_94 = 0;
        }
        else if (*(wchar_t **)((int)param_3 + 0x68) < pwVar1) {
          uVar2 = (int)pwVar1 - (int)*(wchar_t **)((int)param_3 + 0x68);
          if (uVar2 < 3) {
            *(uint *)((int)param_3 + 0x490) = uVar2;
          }
          else {
            *(undefined4 *)((int)param_3 + 0x490) = 2;
          }
          local_b8 = (uint)(uVar2 >= 3);
          FUN_004049a9((void *)((int)param_3 + 0x4c4),*(uint *)((int)param_3 + 0x490),-1);
          uVar2 = FUN_004049a9((void *)((int)param_3 + 0x4b4),*(uint *)((int)param_3 + 0x490),-1);
          if ((((uVar2 & 0xff) != 0) &&
              (uVar2 = FUN_004049a9((void *)((int)param_3 + 0x494),*(uint *)((int)param_3 + 0x490),
                                    -1), (uVar2 & 0xff) != 0)) &&
             (uVar2 = FUN_004049a9((void *)((int)param_3 + 0x4a4),*(uint *)((int)param_3 + 0x490),-1
                                  ), (uVar2 & 0xff) != 0)) {
            puVar6 = &DAT_0040138c;
            if (*(int *)((int)param_3 + 100) == 0) {
              puVar6 = &DAT_004013a0;
            }
            local_90 = *puVar6;
            uStack_8c = puVar6[1];
            uStack_88 = puVar6[2];
            uStack_84 = puVar6[3];
            local_94 = 0;
            if (*(int *)((int)param_3 + 0x490) != 0) {
              do {
                if (1 < local_94) break;
                if ((local_94 == 0) || (local_b8 == 0)) {
                  local_80 = *(int *)((int)param_3 + 0x68) + local_94;
                  local_c8[0] = 0;
                  local_c8[1] = 0;
                  local_c8[2] = 0;
                  local_c8[3] = 0;
                  local_c0 = (wchar_t *)0x0;
                  uStack_bc = 0;
                  uVar2 = (**(code **)(*local_b4 + 0x14))(local_b4,&local_90,local_c8);
                  if ((-1 < (int)uVar2) && (local_c8[0] == 0x1f)) {
                    wcstombs(local_6c,local_c0,100);
                    uVar2 = FUN_00402245(local_6c,(int *)&local_7c);
                  }
                  PropVariantClear((PROPVARIANT *)local_c8);
                  if (-1 < (int)uVar2) goto LAB_00405e6f;
                }
                else {
                  puVar7 = &DAT_004011ec;
                  if (*(int *)((int)param_3 + 100) == 0) {
                    puVar7 = &DAT_004011dc;
                  }
                  local_7c.Data1 = *puVar7;
                  local_7c._4_4_ = puVar7[1];
                  local_7c.Data4._0_4_ = puVar7[2];
                  local_7c.Data4._4_4_ = puVar7[3];
LAB_00405e6f:
                  HVar3 = CoCreateInstance(&local_7c,(LPUNKNOWN)0x0,5,(IID *)&DAT_00401780,&local_9c
                                          );
                  if (-1 < HVar3) {
                    if ((local_b8 == 1) && (local_94 == 1)) {
                      local_a4 = (int *)0x0;
                      (**(code **)*local_9c)(local_9c,&LAB_00401770,&local_a4);
                      if (local_a4 != (int *)0x0) {
                        (**(code **)(*local_a4 + 0xc))(local_a4,*(int *)((int)param_3 + 0x68) + 1);
                        (**(code **)(*local_a4 + 8))(local_a4);
                      }
                    }
                    (**(code **)*local_9c)(local_9c,&DAT_00401760,&local_a0);
                    if (local_a0 != (int *)0x0) {
                      iVar4 = (**(code **)(*local_a0 + 0x18))(local_a0,0x24,param_5);
                      if (iVar4 < 0) {
                        (**(code **)(*local_a0 + 8))(local_a0);
                        local_a0 = (int *)0x0;
                      }
                      else {
                        (**(code **)*local_9c)(local_9c,&DAT_00401750,&local_ac);
                        (**(code **)*local_9c)(local_9c,&LAB_00401740,&local_a8);
                        if ((local_ac == (int *)0x0) || (local_a8 == (int *)0x0)) {
                          if (local_a0 != (int *)0x0) {
                            (**(code **)(*local_a0 + 8))(local_a0);
                            local_a0 = (int *)0x0;
                          }
                          if (local_ac != (int *)0x0) {
                            (**(code **)(*local_ac + 8))(local_ac);
                            local_ac = (int *)0x0;
                          }
                          if (local_a8 != (int *)0x0) {
                            (**(code **)(*local_a8 + 8))(local_a8);
                            local_a8 = (int *)0x0;
                          }
                        }
                        else {
                          FUN_0040311b((void *)((int)param_3 + 0x4a4),local_98,&local_a0);
                          FUN_0040311b((void *)((int)param_3 + 0x494),local_98,&local_ac);
                          FUN_0040311b((void *)((int)param_3 + 0x4b4),local_98,&local_a8);
                          (**(code **)*local_9c)(local_9c,&DAT_00401730,&local_b0);
                          if (local_b0 == (int *)0x0) {
                            local_a4 = (int *)0x0;
                            ppiVar5 = &local_a4;
                          }
                          else {
                            ppiVar5 = &local_b0;
                          }
                          FUN_0040311b((void *)((int)param_3 + 0x4c4),local_98,ppiVar5);
                          local_98 = local_98 + 1;
                        }
                      }
                    }
                    if (local_9c != (int *)0x0) {
                      (**(code **)(*local_9c + 8))(local_9c);
                      local_9c = (int *)0x0;
                    }
                  }
                }
                local_94 = local_94 + 1;
              } while (local_94 < *(uint *)((int)param_3 + 0x490));
              if (local_98 != 0) {
                *(uint *)((int)param_3 + 0x490) = local_98;
                local_94 = 0;
                uVar2 = FUN_004049a9((void *)((int)param_3 + 0x4e8),local_98,-1);
                if ((uVar2 & 0xff) == 0) {
                  local_94 = -0x7fffbffb;
                }
                else {
                  FUN_004049a9((void *)((int)param_3 + 0x4f8),*(uint *)((int)param_3 + 0x490),-1);
                }
                FUN_004056f5(param_3,(uint)pwVar1);
                piVar8 = local_b4;
                goto LAB_00406110;
              }
            }
            *(undefined4 *)((int)param_3 + 0x490) = 0;
            local_94 = 0;
            piVar8 = local_b4;
          }
        }
      }
LAB_00406110:
      (**(code **)(*piVar8 + 8))(piVar8);
      param_2 = extraout_EDX_00;
      goto LAB_0040613c;
    }
  }
  local_94 = -0x7ff8ffa9;
LAB_0040613c:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,param_2);
  return;
}



/* === FUN_00406158 @ 00406158 === */

undefined4 * __fastcall FUN_00406158(undefined4 *param_1)

{
  FUN_00405b28(param_1);
  *param_1 = &PTR_QueryInterface_004017fc;
  param_1[1] = &PTR_LAB_004017e4;
  param_1[2] = &PTR_LAB_004017d0;
  param_1[0xf] = &PTR_LAB_004017c0;
  param_1[0x10] = &PTR_LAB_004017b4;
  param_1[0x142] = &PTR_LAB_0040179c;
  param_1[0x143] = &PTR_LAB_00401790;
  (**(code **)(*DAT_0040d09c + 4))();
  return param_1;
}



/* === FUN_004061ae @ 004061ae === */

void FUN_004061ae(int param_1,_GUID *param_2,undefined4 *param_3,int *param_4)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = *param_4;
  puVar2 = (undefined4 *)(*(code *)param_4[1])();
  FUN_00404851(iVar1 + param_1,puVar2,param_2,param_3);
  return;
}



/* === FUN_004061e1 @ 004061e1 === */

void __fastcall FUN_004061e1(undefined4 *param_1)

{
  *param_1 = &PTR_QueryInterface_004017fc;
  param_1[1] = &PTR_LAB_004017e4;
  param_1[2] = &PTR_LAB_004017d0;
  param_1[0xf] = &PTR_LAB_004017c0;
  param_1[0x10] = &PTR_LAB_004017b4;
  param_1[0x142] = &PTR_LAB_0040179c;
  param_1[0x143] = &PTR_LAB_00401790;
  param_1[0x11] = 0xc0000001;
  FUN_004074f5();
  (**(code **)(*DAT_0040d09c + 8))();
  FUN_00407099(param_1);
  return;
}



/* === Release @ 00406240 === */

/* Library Function - Multiple Matches With Same Base Name
    public: virtual unsigned long __stdcall CEnumMediaTypes::Release(void)
    public: virtual unsigned long __stdcall CEnumPins::Release(void)
   
   Library: Visual Studio 2019 Release */

LONG Release(int *param_1)

{
  LONG LVar1;
  
  LVar1 = InterlockedDecrement(param_1 + 0x11);
  if ((LVar1 == 0) && (param_1 != (int *)0x0)) {
    (**(code **)(*param_1 + 0x28))(1);
  }
  return LVar1;
}



/* === FUN_00406274 @ 00406274 === */

undefined4 * __thiscall FUN_00406274(void *this,byte param_1)

{
  FUN_004061e1(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === _InternalQueryInterface @ 004062eb === */

/* Library Function - Single Match
    public: long __thiscall ATL::CAccessibleProxy::_InternalQueryInterface(struct _GUID const &,void
   * *)
   
   Library: Visual Studio 2008 Release */

long __thiscall
ATL::CAccessibleProxy::_InternalQueryInterface(CAccessibleProxy *this,_GUID *param_1,void **param_2)

{
  int iVar1;
  
  iVar1 = FUN_00404851((int)this,&PTR_DAT_00401830,param_1,param_2);
  return iVar1;
}



/* === QueryInterface @ 0040630a === */

/* Library Function - Single Match
    public: virtual long __stdcall CMFCComObject<class ATL::CAccessibleProxy>::QueryInterface(struct
   _GUID const &,void * *)
   
   Library: Visual Studio 2008 Release */

long CMFCComObject<ATL::CAccessibleProxy>::QueryInterface(_GUID *param_1,void **param_2)

{
  long lVar1;
  void **in_stack_0000000c;
  
  lVar1 = ATL::CAccessibleProxy::_InternalQueryInterface
                    ((CAccessibleProxy *)param_1,(_GUID *)param_2,in_stack_0000000c);
  return lVar1;
}



/* === FUN_00406386 @ 00406386 === */

undefined4 * __fastcall FUN_00406386(undefined4 *param_1)

{
  FUN_00405b78(param_1);
  *param_1 = &PTR_QueryInterface_0040191c;
  param_1[1] = &PTR_LAB_00401904;
  param_1[2] = &PTR_LAB_004018f0;
  param_1[0xf] = &PTR_LAB_004018e0;
  param_1[0x10] = &PTR_LAB_004018d4;
  param_1[0x142] = &PTR_LAB_004018c8;
  (**(code **)(*DAT_0040d09c + 4))();
  return param_1;
}



/* === FUN_004063d2 @ 004063d2 === */

void __fastcall FUN_004063d2(undefined4 *param_1)

{
  *param_1 = &PTR_QueryInterface_0040191c;
  param_1[1] = &PTR_LAB_00401904;
  param_1[2] = &PTR_LAB_004018f0;
  param_1[0xf] = &PTR_LAB_004018e0;
  param_1[0x10] = &PTR_LAB_004018d4;
  param_1[0x142] = &PTR_LAB_004018c8;
  param_1[0x11] = 0xc0000001;
  FUN_004074f5();
  (**(code **)(*DAT_0040d09c + 8))();
  FUN_004074fb(param_1);
  return;
}



/* === FUN_00406427 @ 00406427 === */

void FUN_00406427(int param_1)

{
  InterlockedIncrement((LONG *)(param_1 + 0x44));
  return;
}



/* === FUN_00406442 @ 00406442 === */

undefined4 * __thiscall FUN_00406442(void *this,byte param_1)

{
  FUN_004063d2(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === _InternalQueryInterface @ 004064d7 === */

/* Library Function - Single Match
    public: long __thiscall ATL::CAccessibleProxy::_InternalQueryInterface(struct _GUID const &,void
   * *)
   
   Library: Visual Studio 2008 Release */

long __thiscall
ATL::CAccessibleProxy::_InternalQueryInterface(CAccessibleProxy *this,_GUID *param_1,void **param_2)

{
  int iVar1;
  
  iVar1 = FUN_00404851((int)this,&PTR_DAT_00401950,param_1,param_2);
  return iVar1;
}



/* === QueryInterface @ 004064f6 === */

/* Library Function - Single Match
    public: virtual long __stdcall CMFCComObject<class ATL::CAccessibleProxy>::QueryInterface(struct
   _GUID const &,void * *)
   
   Library: Visual Studio 2008 Release */

long CMFCComObject<ATL::CAccessibleProxy>::QueryInterface(_GUID *param_1,void **param_2)

{
  long lVar1;
  void **in_stack_0000000c;
  
  lVar1 = ATL::CAccessibleProxy::_InternalQueryInterface
                    ((CAccessibleProxy *)param_1,(_GUID *)param_2,in_stack_0000000c);
  return lVar1;
}



/* === FUN_00406560 @ 00406560 === */

undefined4 * __thiscall FUN_00406560(void *this,undefined4 param_1)

{
  FUN_00405b28(this);
  *(undefined4 *)((int)this + 0x44) = param_1;
  *(undefined ***)this = &PTR_FUN_004019cc;
  *(undefined ***)((int)this + 4) = &PTR_LAB_00401a2c;
  *(undefined ***)((int)this + 8) = &PTR_LAB_004019b8;
  *(undefined ***)((int)this + 0x3c) = &PTR_LAB_004019a8;
  *(undefined ***)((int)this + 0x40) = &PTR_LAB_00401a0c;
  *(undefined ***)((int)this + 0x508) = &PTR_LAB_00401990;
  *(undefined ***)((int)this + 0x50c) = &PTR_LAB_00401984;
  return this;
}



/* === FUN_004065b5 @ 004065b5 === */

void FUN_004065b5(int param_1)

{
  (**(code **)(**(int **)(param_1 + 0x44) + 4))(*(int **)(param_1 + 0x44));
  return;
}



/* === FUN_004065cf @ 004065cf === */

void FUN_004065cf(int param_1)

{
  (**(code **)(**(int **)(param_1 + 0x44) + 8))(*(int **)(param_1 + 0x44));
  return;
}



/* === FUN_004065e9 @ 004065e9 === */

void FUN_004065e9(int param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)**(undefined4 **)(param_1 + 0x44))(*(undefined4 **)(param_1 + 0x44),param_2,param_3);
  return;
}



/* === FUN_00406608 @ 00406608 === */

undefined4 * __thiscall FUN_00406608(void *this,byte param_1)

{
  FUN_00407099(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === FUN_004066b5 @ 004066b5 === */

undefined4 * __thiscall FUN_004066b5(void *this,undefined4 param_1)

{
  FUN_00405b78(this);
  *(undefined4 *)((int)this + 0x44) = param_1;
  *(undefined ***)this = &PTR_FUN_00401a44;
  *(undefined ***)((int)this + 4) = &PTR_LAB_00401a2c;
  *(undefined ***)((int)this + 8) = &PTR_LAB_00401a18;
  *(undefined ***)((int)this + 0x3c) = &PTR_LAB_004019a8;
  *(undefined ***)((int)this + 0x40) = &PTR_LAB_00401a0c;
  *(undefined ***)((int)this + 0x508) = &PTR_LAB_00401a00;
  return this;
}



/* === FUN_00406799 @ 00406799 === */

void FUN_00406799(LPCWSTR param_1,LPCWSTR param_2,LPCWSTR param_3,int param_4)

{
  HRSRC hResInfo;
  LPCSTR lpMultiByteStr;
  DWORD cbMultiByte;
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int local_41c [2];
  int local_414;
  HMODULE local_410;
  LPWSTR local_40c;
  WCHAR local_408 [512];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_414 = 0;
  local_41c[0] = 0;
  local_40c = (WCHAR *)0x0;
  local_410 = LoadLibraryExW(param_1,(HANDLE)0x0,2);
  if (local_410 == (HMODULE)0x0) {
    FUN_00402847();
  }
  else {
    hResInfo = FindResourceW(local_410,param_2,param_3);
    if ((hResInfo == (HRSRC)0x0) ||
       (lpMultiByteStr = LoadResource(local_410,hResInfo), lpMultiByteStr == (LPCSTR)0x0)) {
LAB_00406803:
      FUN_00402847();
    }
    else {
      cbMultiByte = SizeofResource(local_410,hResInfo);
      if (cbMultiByte + 1 < cbMultiByte) {
        if (local_40c != local_408) {
          FUN_004030e4(&local_40c);
        }
        goto LAB_00406854;
      }
      FUN_0040474d(&local_40c,cbMultiByte + 1);
      if (local_40c != (LPWSTR)0x0) {
        iVar1 = MultiByteToWideChar(3,0,lpMultiByteStr,cbMultiByte,local_40c,cbMultiByte);
        if (iVar1 == 0) goto LAB_00406803;
        local_40c[iVar1] = L'\0';
        FUN_004059e4(local_41c,extraout_EDX_00,local_40c,param_4);
      }
    }
    FreeLibrary(local_410);
  }
  if (local_40c != local_408) {
    FUN_004030e4(&local_40c);
  }
LAB_00406854:
  FUN_00402fd1(&local_414);
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,extraout_EDX);
  return;
}



/* === FUN_004068fa @ 004068fa === */

undefined4 FUN_004068fa(undefined4 param_1,LPCWSTR param_2,ushort param_3,LPCWSTR param_4)

{
  undefined4 uVar1;
  int local_8;
  
  local_8 = 0;
  uVar1 = FUN_00406799(param_2,(LPCWSTR)(uint)param_3,param_4,1);
  FUN_00402fd1(&local_8);
  return uVar1;
}



/* === FUN_00406930 @ 00406930 === */

undefined4 FUN_00406930(undefined4 param_1,LPCWSTR param_2,ushort param_3,LPCWSTR param_4)

{
  undefined4 uVar1;
  int local_8;
  
  local_8 = 0;
  uVar1 = FUN_00406799(param_2,(LPCWSTR)(uint)param_3,param_4,0);
  FUN_00402fd1(&local_8);
  return uVar1;
}



/* === FUN_00406966 @ 00406966 === */

void FUN_00406966(int *param_1,ushort param_2,int param_3,undefined4 *param_4)

{
  HMODULE pHVar1;
  bool bVar2;
  int iVar3;
  DWORD DVar4;
  HMODULE pHVar5;
  LPCWSTR pWVar6;
  undefined4 extraout_EDX;
  undefined4 uVar7;
  undefined4 extraout_EDX_00;
  undefined4 local_a68 [4];
  CComCriticalSection local_a58 [28];
  int local_a3c;
  WCHAR local_a38 [520];
  WCHAR local_628;
  undefined2 local_626 [523];
  WCHAR local_210 [260];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  FUN_00405421(local_a68);
  iVar3 = FUN_0040282e(local_a58);
  if (iVar3 < 0) {
    FUN_00404310(local_a68);
    uVar7 = extraout_EDX;
    goto LAB_004069ad;
  }
  if (param_4 != (undefined4 *)0x0) {
    for (; (LPCWSTR)*param_4 != (LPCWSTR)0x0; param_4 = param_4 + 2) {
      FUN_00404b3c((int)local_a68,(LPCWSTR)*param_4,(LPCWSTR)param_4[1]);
    }
  }
  iVar3 = (**(code **)(*param_1 + 0x14))(local_a68);
  pHVar1 = DAT_0040d118;
  if (-1 < iVar3) {
    local_a3c = 0;
    DVar4 = GetModuleFileNameW(DAT_0040d118,local_210,0x104);
    if (DVar4 == 0) {
      FUN_00402847();
    }
    else {
      if (DVar4 == 0x104) {
        FUN_00402fd1(&local_a3c);
        goto LAB_004069f3;
      }
      FUN_004028ba((int)local_a38,0x208,local_210);
      if ((pHVar1 == (HMODULE)0x0) || (pHVar5 = GetModuleHandleW((LPCWSTR)0x0), pHVar1 == pHVar5)) {
        local_628 = L'\"';
        bVar2 = FUN_004026bf(local_626,0x20b,local_a38);
        if (!bVar2) {
          FUN_00402fd1(&local_a3c);
          goto LAB_004069f3;
        }
        iVar3 = lstrlenW(&local_628);
        local_626[iVar3 + -1] = 0x22;
        local_626[iVar3] = 0;
        pWVar6 = &local_628;
      }
      else {
        pWVar6 = local_a38;
      }
      iVar3 = FUN_00404b3c((int)local_a68,L"Module",pWVar6);
      if ((-1 < iVar3) && (iVar3 = FUN_00404b3c((int)local_a68,L"Module_Raw",local_a38), -1 < iVar3)
         ) {
        if (param_3 == 0) {
          FUN_00406930(local_a68,local_210,param_2,L"REGISTRY");
        }
        else {
          FUN_004068fa(local_a68,local_210,param_2,L"REGISTRY");
        }
      }
    }
    FUN_00402fd1(&local_a3c);
  }
LAB_004069f3:
  FUN_00404310(local_a68);
  uVar7 = extraout_EDX_00;
LAB_004069ad:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar7);
  return;
}



/* === FUN_00406b52 @ 00406b52 === */

void FUN_00406b52(int param_1)

{
  FUN_00406966(DAT_0040d09c,0x6e,param_1,(undefined4 *)0x0);
  return;
}



/* === FUN_00406b72 @ 00406b72 === */

void FUN_00406b72(int param_1)

{
  FUN_00406966(DAT_0040d09c,0x6f,param_1,(undefined4 *)0x0);
  return;
}



/* === FUN_00406b92 @ 00406b92 === */

int FUN_00406b92(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  if (param_3 == (undefined4 *)0x0) {
    iVar1 = -0x7fffbffd;
  }
  else {
    *param_3 = 0;
    iVar1 = -0x7ff8fff2;
    puVar2 = LocalAlloc(0x40,0x510);
    if (puVar2 == (undefined4 *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = FUN_00406158(puVar2);
    }
    if (piVar3 != (int *)0x0) {
      InterlockedIncrement(piVar3 + 0x11);
      iVar1 = FUN_0040282e((CComCriticalSection *)(piVar3 + 0x12));
      if ((-1 < iVar1) && (iVar1 = FUN_00407177((int)piVar3), -1 < iVar1)) {
        iVar1 = 0;
      }
      InterlockedDecrement(piVar3 + 0x11);
      if ((iVar1 != 0) || (iVar1 = (**(code **)*piVar3)(piVar3,param_2,param_3), iVar1 != 0)) {
        (**(code **)(*piVar3 + 0x28))(1);
      }
    }
  }
  return iVar1;
}



/* === FUN_00406c32 @ 00406c32 === */

int FUN_00406c32(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  if (param_3 == (undefined4 *)0x0) {
    iVar1 = -0x7fffbffd;
  }
  else {
    *param_3 = 0;
    iVar1 = -0x7ff8fff2;
    puVar2 = LocalAlloc(0x40,0x50c);
    if (puVar2 == (undefined4 *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = FUN_00406386(puVar2);
    }
    if (piVar3 != (int *)0x0) {
      InterlockedIncrement(piVar3 + 0x11);
      iVar1 = FUN_0040282e((CComCriticalSection *)(piVar3 + 0x12));
      if ((-1 < iVar1) && (iVar1 = FUN_00407531((int)piVar3), -1 < iVar1)) {
        iVar1 = 0;
      }
      InterlockedDecrement(piVar3 + 0x11);
      if ((iVar1 != 0) || (iVar1 = (**(code **)*piVar3)(piVar3,param_2,param_3), iVar1 != 0)) {
        (**(code **)(*piVar3 + 0x28))(1);
      }
    }
  }
  return iVar1;
}



/* === FUN_00406cd2 @ 00406cd2 === */

undefined4 * __thiscall FUN_00406cd2(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined ***)this = &PTR_FUN_00401ab4;
  FUN_00406560((void *)((int)this + 0xc),param_1);
  (**(code **)(*DAT_0040d09c + 4))();
  return this;
}



/* === FUN_00406d06 @ 00406d06 === */

void __fastcall FUN_00406d06(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_00401ab4;
  param_1[1] = 0xc0000001;
  FUN_004074f5();
  (**(code **)(*DAT_0040d09c + 8))();
  FUN_00407099(param_1 + 3);
  return;
}



/* === FUN_00406d38 @ 00406d38 === */

long FUN_00406d38(int *param_1,_GUID *param_2,void **param_3)

{
  int iVar1;
  long lVar2;
  
  lVar2 = 0;
  if (param_3 == (void **)0x0) {
    lVar2 = -0x7fffbffd;
  }
  else {
    *param_3 = (void *)0x0;
    iVar1 = ATL::InlineIsEqualUnknown(param_2);
    if (iVar1 == 0) {
      lVar2 = ATL::CAccessibleProxy::_InternalQueryInterface
                        ((CAccessibleProxy *)(param_1 + 3),param_2,param_3);
    }
    else {
      *param_3 = param_1;
      (**(code **)(*param_1 + 4))(param_1);
    }
  }
  return lVar2;
}



/* === FUN_00406d88 @ 00406d88 === */

undefined4 * __thiscall FUN_00406d88(void *this,byte param_1)

{
  FUN_00406d06(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === FUN_00406dae @ 00406dae === */

undefined4 * __thiscall FUN_00406dae(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined ***)this = &PTR_FUN_00401ac4;
  FUN_004066b5((void *)((int)this + 0xc),param_1);
  (**(code **)(*DAT_0040d09c + 4))();
  return this;
}



/* === FUN_00406de2 @ 00406de2 === */

void __fastcall FUN_00406de2(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_00401ac4;
  param_1[1] = 0xc0000001;
  FUN_004074f5();
  (**(code **)(*DAT_0040d09c + 8))();
  FUN_004074fb(param_1 + 3);
  return;
}



/* === FUN_00406e14 @ 00406e14 === */

void FUN_00406e14(int param_1)

{
  InterlockedIncrement((LONG *)(param_1 + 4));
  return;
}



/* === Release @ 00406e2f === */

/* Library Function - Multiple Matches With Same Base Name
    public: virtual unsigned long __stdcall CEnumMediaTypes::Release(void)
    public: virtual unsigned long __stdcall CEnumPins::Release(void)
   
   Library: Visual Studio 2019 Release */

LONG Release(int *param_1)

{
  LONG LVar1;
  
  LVar1 = InterlockedDecrement(param_1 + 1);
  if ((LVar1 == 0) && (param_1 != (int *)0x0)) {
    (**(code **)(*param_1 + 0xc))(1);
  }
  return LVar1;
}



/* === FUN_00406e63 @ 00406e63 === */

long FUN_00406e63(int *param_1,_GUID *param_2,void **param_3)

{
  int iVar1;
  long lVar2;
  
  lVar2 = 0;
  if (param_3 == (void **)0x0) {
    lVar2 = -0x7fffbffd;
  }
  else {
    *param_3 = (void *)0x0;
    iVar1 = ATL::InlineIsEqualUnknown(param_2);
    if (iVar1 == 0) {
      lVar2 = ATL::CAccessibleProxy::_InternalQueryInterface
                        ((CAccessibleProxy *)(param_1 + 3),param_2,param_3);
    }
    else {
      *param_3 = param_1;
      (**(code **)(*param_1 + 4))(param_1);
    }
  }
  return lVar2;
}



/* === FUN_00406eb3 @ 00406eb3 === */

undefined4 * __thiscall FUN_00406eb3(void *this,byte param_1)

{
  FUN_00406de2(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === FUN_00406ed9 @ 00406ed9 === */

int FUN_00406ed9(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  HLOCAL this;
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)0x0;
  if (param_3 == (undefined4 *)0x0) {
    return -0x7fffbffd;
  }
  *param_3 = 0;
  this = LocalAlloc(0x40,0x51c);
  if (this != (HLOCAL)0x0) {
    piVar2 = FUN_00406cd2(this,param_1);
  }
  if (piVar2 == (int *)0x0) {
    return -0x7ff8fff2;
  }
  iVar1 = FUN_0040282e((CComCriticalSection *)(piVar2 + 0x15));
  if (-1 < iVar1) {
    iVar1 = 0;
  }
  if (-1 < iVar1) {
    iVar1 = FUN_00407177((int)(piVar2 + 3));
    if (iVar1 < 0) goto LAB_00406f50;
    iVar1 = 0;
  }
  if ((iVar1 == 0) && (iVar1 = (**(code **)*piVar2)(piVar2,param_2,param_3), iVar1 == 0)) {
    return 0;
  }
LAB_00406f50:
  (**(code **)(*piVar2 + 0xc))(1);
  return iVar1;
}



/* === FUN_00406f67 @ 00406f67 === */

int FUN_00406f67(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  HLOCAL this;
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)0x0;
  if (param_3 == (undefined4 *)0x0) {
    return -0x7fffbffd;
  }
  *param_3 = 0;
  this = LocalAlloc(0x40,0x518);
  if (this != (HLOCAL)0x0) {
    piVar2 = FUN_00406dae(this,param_1);
  }
  if (piVar2 == (int *)0x0) {
    return -0x7ff8fff2;
  }
  iVar1 = FUN_0040282e((CComCriticalSection *)(piVar2 + 0x15));
  if (-1 < iVar1) {
    iVar1 = 0;
  }
  if (-1 < iVar1) {
    iVar1 = FUN_00407531((int)(piVar2 + 3));
    if (iVar1 < 0) goto LAB_00406fde;
    iVar1 = 0;
  }
  if ((iVar1 == 0) && (iVar1 = (**(code **)*piVar2)(piVar2,param_2,param_3), iVar1 == 0)) {
    return 0;
  }
LAB_00406fde:
  (**(code **)(*piVar2 + 0xc))(1);
  return iVar1;
}



/* === FUN_00406ff5 @ 00406ff5 === */

void FUN_00406ff5(int param_1,undefined4 param_2,undefined4 *param_3)

{
  if (param_1 == 0) {
    FUN_00406b92(0,param_2,param_3);
    return;
  }
  FUN_00406ed9(param_1,param_2,param_3);
  return;
}



/* === FUN_0040701c @ 0040701c === */

void FUN_0040701c(int param_1,undefined4 param_2,undefined4 *param_3)

{
  if (param_1 == 0) {
    FUN_00406c32(0,param_2,param_3);
    return;
  }
  FUN_00406f67(param_1,param_2,param_3);
  return;
}



/* === StringCopyWorkerW @ 00407043 === */

/* Library Function - Single Match
    long __stdcall StringCopyWorkerW(unsigned short *,unsigned int,unsigned int *,unsigned short
   const *,unsigned int)
   
   Library: Visual Studio 2008 Release */

long StringCopyWorkerW(ushort *param_1,uint param_2,uint *param_3,ushort *param_4,uint param_5)

{
  short *in_EAX;
  long lVar1;
  short *in_ECX;
  int in_EDX;
  int iVar2;
  
  lVar1 = 0;
  iVar2 = 0;
  if (in_EDX != 0) {
    do {
      if ((param_2 == 0) || (*in_EAX == 0)) break;
      *in_ECX = *in_EAX;
      in_ECX = in_ECX + 1;
      in_EAX = in_EAX + 1;
      in_EDX = in_EDX + -1;
      param_2 = param_2 - 1;
      iVar2 = iVar2 + 1;
    } while (in_EDX != 0);
    if (in_EDX != 0) goto LAB_00407080;
  }
  in_ECX = in_ECX + -1;
  iVar2 = iVar2 + -1;
  lVar1 = -0x7ff8ff86;
LAB_00407080:
  *in_ECX = 0;
  if (param_1 != (ushort *)0x0) {
    *(int *)param_1 = iVar2;
  }
  return lVar1;
}



/* === FUN_00407099 @ 00407099 === */

void __fastcall FUN_00407099(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_0040169c;
  param_1[1] = &PTR_LAB_004016e4;
  param_1[2] = &PTR_LAB_00401688;
  param_1[0xf] = &PTR_LAB_00401678;
  param_1[0x10] = &PTR_LAB_0040166c;
  param_1[0x142] = &PTR_LAB_00401654;
  param_1[0x143] = &PTR_LAB_0040166c;
  FUN_00405538(param_1);
  return;
}



/* === FUN_004070d9 @ 004070d9 === */

void FUN_004070d9(int param_1,int *param_2)

{
  FUN_00403921((void *)(param_1 + -0x508),param_2);
  return;
}



/* === FUN_004070f8 @ 004070f8 === */

void FUN_004070f8(int param_1,uint param_2,undefined4 *param_3)

{
  FUN_00403986((void *)(param_1 + -0x508),param_2,param_3);
  return;
}



/* === FUN_0040711a @ 0040711a === */

void FUN_0040711a(int param_1,uint param_2,int param_3)

{
  FUN_00403a44((void *)(param_1 + -0x508),param_2,param_3);
  return;
}



/* === _RtlStringCbCopyW@12 @ 0040713c === */

/* Library Function - Single Match
    _RtlStringCbCopyW@12
   
   Library: Visual Studio 2019 Release */

void _RtlStringCbCopyW_12(uint param_1,uint param_2)

{
  int iVar1;
  uint *unaff_EBP;
  ushort *unaff_retaddr;
  
  iVar1 = 0;
  if ((param_2 >> 1 == 0) || (0x7fffffff < param_2 >> 1)) {
    iVar1 = -0x7ff8ffa9;
  }
  if (-1 < iVar1) {
    StringCopyWorkerW((ushort *)0x0,0x7ffffffe,unaff_EBP,unaff_retaddr,param_1);
  }
  return;
}



/* === FUN_00407177 @ 00407177 === */

undefined4 __fastcall FUN_00407177(int param_1)

{
  *(undefined4 *)(param_1 + 0x6c) = DAT_004011ec;
  *(undefined4 *)(param_1 + 0x70) = DAT_004011f0;
  *(undefined4 *)(param_1 + 0x74) = DAT_004011f4;
  *(undefined4 *)(param_1 + 0x78) = DAT_004011f8;
  memset((short *)(param_1 + 0x7c),0,0x200);
  memset((void *)(param_1 + 0x27c),0,0x200);
  FUN_0040346a((short *)(param_1 + 0x7c),0x200,0x401b44);
  FUN_0040346a((short *)(param_1 + 0x27c),0x200,0x401af8);
  *(undefined4 *)(param_1 + 0x47c) = DAT_00401860;
  *(undefined4 *)(param_1 + 0x480) = DAT_00401864;
  *(undefined4 *)(param_1 + 0x484) = DAT_00401868;
  *(undefined4 *)(param_1 + 0x488) = DAT_0040186c;
  return 0;
}



/* === FUN_004071e5 @ 004071e5 === */

int __thiscall
FUN_004071e5(void *this,IAudioMediaType *param_1,IAudioMediaType **param_2,int param_3,int *param_4)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int local_8;
  
  local_8 = 0;
  if ((param_1 == (IAudioMediaType *)0x0) ||
     ((**(code **)(*(int *)param_1 + 0xc))(param_1,&local_8), local_8 == 0)) {
    iVar4 = FUN_0040467f(this,param_1,param_2,param_4);
    return iVar4;
  }
  puVar3 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),0);
  piVar1 = (int *)*puVar3;
  puVar3 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),1);
  piVar2 = (int *)*puVar3;
  iVar4 = FUN_00402f85((int)param_2,piVar1);
  if (iVar4 != 0) {
    return iVar4;
  }
  iVar4 = (**(code **)(*piVar2 + 0x1c))(piVar2,param_1,param_2,param_4);
  if (iVar4 != 0) {
    return iVar4;
  }
  if (param_3 == 0) {
    return 0;
  }
  FUN_0040311b((void *)((int)this + 0x4e8),0,&param_2);
  (**(code **)(*param_2 + 4))(param_2);
  return 0;
}



/* === FUN_00407289 @ 00407289 === */

int __thiscall FUN_00407289(void *this,int *param_1,int *param_2,int param_3,int *param_4)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int local_8;
  
  piVar1 = param_2;
  local_8 = 0;
  if ((param_2 == (int *)0x0) || ((**(code **)(*param_2 + 0xc))(param_2,&local_8), local_8 == 0)) {
    iVar4 = FUN_004046b7(this,param_1,piVar1,param_4);
    return iVar4;
  }
  puVar3 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),0);
  piVar1 = (int *)*puVar3;
  puVar3 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),1);
  piVar2 = (int *)*puVar3;
  iVar4 = FUN_00402f85((int)param_1,piVar1);
  if (iVar4 != 0) {
    return iVar4;
  }
  iVar4 = (**(code **)(*piVar2 + 0x20))(piVar2,param_1,param_2,param_4);
  if (iVar4 != 0) {
    return iVar4;
  }
  if (param_3 == 0) {
    return 0;
  }
  FUN_0040311b((void *)((int)this + 0x4e8),0,&param_1);
  (**(code **)(*param_1 + 4))(param_1);
  return 0;
}



/* === FUN_0040732d @ 0040732d === */

undefined4 * __cdecl
FUN_0040732d(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 *param_7,undefined4 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  param_1[4] = param_8;
  _RtlStringCbCopyW_12((uint)(param_1 + 5),0x200);
  _RtlStringCbCopyW_12((uint)(param_1 + 0x85),0x200);
  param_1[0x105] = param_5;
  param_1[0x106] = param_6;
  param_1[0x107] = param_9;
  param_1[0x108] = param_10;
  param_1[0x109] = param_11;
  param_1[0x10a] = param_12;
  param_1[0x10b] = param_13;
  param_1[0x10c] = 1;
  param_1[0x10d] = *param_7;
  param_1[0x10e] = param_7[1];
  param_1[0x10f] = param_7[2];
  param_1[0x110] = param_7[3];
  return param_1;
}



/* === FUN_004073cb @ 004073cb === */

void FUN_004073cb(IAudioMediaType *param_1,IAudioMediaType *param_2,IAudioMediaType **param_3,
                 int *param_4)

{
  IAudioMediaType *this;
  IAudioMediaType *pIVar1;
  int iVar2;
  short local_18 [8];
  int local_8;
  
  this = param_1;
  local_18[0] = 0;
  local_18[1] = 0;
  local_18[2] = 0;
  local_18[3] = 0;
  local_18[4] = 0;
  local_18[5] = 0;
  local_18[6] = 0;
  local_18[7] = 0;
  local_8 = 0;
  iVar2 = (**(code **)(**(int **)(param_1 + 0x4e4) + 0x14))
                    (*(int **)(param_1 + 0x4e4),&DAT_004013dc,local_18);
  if ((-1 < iVar2) && (local_18[0] == 0xb)) {
    local_8 = (int)local_18[4];
  }
  PropVariantClear((PROPVARIANT *)local_18);
  pIVar1 = param_2;
  param_1 = (IAudioMediaType *)0x0;
  if (((param_2 != (IAudioMediaType *)0x0) &&
      ((**(code **)(*(int *)param_2 + 0xc))(param_2,&param_1), param_1 != (IAudioMediaType *)0x0))
     && (local_8 != 0)) {
    FUN_004071e5(this,pIVar1,param_3,0,param_4);
    return;
  }
  FUN_0040467f(this,pIVar1,param_3,param_4);
  return;
}



/* === FUN_00407460 @ 00407460 === */

void FUN_00407460(void *param_1,int *param_2,int *param_3,int *param_4)

{
  void *this;
  int *piVar1;
  int iVar2;
  short local_18 [8];
  int local_8;
  
  this = param_1;
  local_18[0] = 0;
  local_18[1] = 0;
  local_18[2] = 0;
  local_18[3] = 0;
  local_18[4] = 0;
  local_18[5] = 0;
  local_18[6] = 0;
  local_18[7] = 0;
  local_8 = 0;
  iVar2 = (**(code **)(**(int **)((int)param_1 + 0x4e4) + 0x14))
                    (*(int **)((int)param_1 + 0x4e4),&DAT_004013dc,local_18);
  if ((-1 < iVar2) && (local_18[0] == 0xb)) {
    local_8 = (int)local_18[4];
  }
  PropVariantClear((PROPVARIANT *)local_18);
  piVar1 = param_3;
  param_1 = (void *)0x0;
  if (((param_3 != (int *)0x0) &&
      ((**(code **)(*param_3 + 0xc))(param_3,&param_1), param_1 != (void *)0x0)) && (local_8 != 0))
  {
    FUN_00407289(this,param_2,piVar1,0,param_4);
    return;
  }
  FUN_004046b7(this,param_2,piVar1,param_4);
  return;
}



/* === FUN_004074f5 @ 004074f5 === */

void FUN_004074f5(void)

{
  return;
}



/* === FUN_004074fb @ 004074fb === */

void __fastcall FUN_004074fb(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_004016fc;
  param_1[1] = &PTR_LAB_004016e4;
  param_1[2] = &PTR_LAB_004016d0;
  param_1[0xf] = &PTR_LAB_00401678;
  param_1[0x10] = &PTR_LAB_0040166c;
  param_1[0x142] = &PTR_LAB_0040166c;
  FUN_00405538(param_1);
  return;
}



/* === FUN_00407531 @ 00407531 === */

undefined4 __fastcall FUN_00407531(int param_1)

{
  *(undefined4 *)(param_1 + 0x6c) = DAT_004011dc;
  *(undefined4 *)(param_1 + 0x70) = DAT_004011e0;
  *(undefined4 *)(param_1 + 0x74) = DAT_004011e4;
  *(undefined4 *)(param_1 + 0x78) = DAT_004011e8;
  memset((short *)(param_1 + 0x7c),0,0x200);
  memset((void *)(param_1 + 0x27c),0,0x200);
  FUN_0040346a((short *)(param_1 + 0x7c),0x200,0x401bb0);
  FUN_0040346a((short *)(param_1 + 0x27c),0x200,0x401af8);
  *(undefined4 *)(param_1 + 0x47c) = DAT_00401974;
  *(undefined4 *)(param_1 + 0x480) = DAT_00401978;
  *(undefined4 *)(param_1 + 0x484) = DAT_0040197c;
  *(undefined4 *)(param_1 + 0x488) = DAT_00401980;
  return 0;
}



/* === FUN_0040759f @ 0040759f === */

undefined4 __fastcall FUN_0040759f(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  short *psVar6;
  short local_1c [4];
  int local_14;
  undefined4 uStack_10;
  uint local_c;
  uint local_8;
  
  local_8 = 0;
  local_c = *(uint *)(param_1 + 0x4d8);
  if (local_c != 0) {
    do {
      local_1c[0] = 0;
      local_1c[1] = 0;
      local_1c[2] = 0;
      local_1c[3] = 0;
      local_14 = 0;
      uStack_10 = 0;
      piVar1 = (int *)FUN_0040319b((void *)(param_1 + 0x4d4),local_8);
      iVar3 = 4;
      bVar5 = true;
      piVar4 = &DAT_00401644;
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar5 = *piVar1 == *piVar4;
        piVar1 = piVar1 + 1;
        piVar4 = piVar4 + 1;
      } while (bVar5);
      if (!bVar5) {
        piVar1 = *(int **)(param_1 + 0x4e4);
        iVar3 = *piVar1;
        psVar6 = local_1c;
        iVar2 = FUN_0040319b((void *)(param_1 + 0x4d4),local_8);
        iVar3 = (**(code **)(iVar3 + 0x14))(piVar1,iVar2,psVar6);
        if (-1 < iVar3) {
          if (local_1c[0] == 0x13) {
            if (((local_14 == -1) || (local_14 == 0)) || (local_14 == 1)) {
              iVar3 = FUN_0040319b((void *)(param_1 + 0x4d4),local_8);
              *(int *)(iVar3 + 0x14) = local_14;
            }
          }
          else if ((local_1c[0] == 0xb) && (((short)local_14 == 0 || ((short)local_14 == 1)))) {
            iVar2 = (int)(short)local_14;
            iVar3 = FUN_0040319b((void *)(param_1 + 0x4d4),local_8);
            *(int *)(iVar3 + 0x14) = iVar2;
          }
        }
      }
      PropVariantClear((PROPVARIANT *)local_1c);
      local_8 = local_8 + 1;
    } while (local_8 < local_c);
  }
  return 0;
}



/* === FUN_00407689 @ 00407689 === */

undefined4 __thiscall FUN_00407689(void *this,int param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = *(uint *)((int)this + 0x4d8);
  uVar3 = 0;
  if (uVar1 != 0) {
    do {
      iVar2 = FUN_0040319b((void *)((int)this + 0x4d4),uVar3);
      if (*(int *)(iVar2 + 0x14) == param_1) {
        *param_2 = uVar3;
        return 0;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar1);
  }
  return 0x80004005;
}



/* === FUN_004076d2 @ 004076d2 === */

void __fastcall FUN_004076d2(void *param_1)

{
  LSTATUS LVar1;
  wchar_t *pwVar2;
  int iVar3;
  DWORD DVar4;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 uVar5;
  char *pcVar6;
  bool bVar7;
  uint local_e8;
  int local_e4;
  DWORD local_e0;
  HKEY local_dc;
  DWORD local_d8 [2];
  wchar_t local_d0;
  undefined1 local_ce [198];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_d8[1] = 1;
  local_d8[0] = 100;
  local_dc = (HKEY)0x0;
  local_d0 = L'\0';
  memset(local_ce,0,0xc6);
  uVar5 = extraout_EDX;
  if ((*(int *)((int)param_1 + 0x490) == 2) &&
     (LVar1 = RegOpenKeyW((HKEY)0x80000002,L"Software\\Creative Tech\\Sound Blaster X-Fi MB",
                          &local_dc), uVar5 = extraout_EDX_00, LVar1 == 0)) {
    LVar1 = RegQueryValueExW(local_dc,L"Lockid",(LPDWORD)0x0,&local_e0,(LPBYTE)&local_d0,local_d8);
    if (LVar1 == 0) {
      DVar4 = local_d8[0];
      pwVar2 = _wcsupr(&local_d0);
      memcpy(&local_d0,pwVar2,DVar4);
      bVar7 = true;
      DVar4 = local_d8[0];
      pwVar2 = &local_d0;
      pcVar6 = "F";
      do {
        if (DVar4 == 0) break;
        DVar4 = DVar4 - 1;
        bVar7 = (char)*pwVar2 == *pcVar6;
        pwVar2 = (wchar_t *)((int)pwVar2 + 1);
        pcVar6 = pcVar6 + 1;
      } while (bVar7);
      if (bVar7) {
        local_d8[0] = 100;
        LVar1 = RegQueryValueExW(local_dc,L"UpDownMixCoExistSupport",(LPDWORD)0x0,&local_e0,
                                 (LPBYTE)&local_e4,local_d8);
        if ((LVar1 == 0) && (local_e4 == 1)) {
          uVar5 = extraout_EDX_01;
          if (*(int *)((int)param_1 + 0x4d8) != 0) {
            FUN_0040759f((int)param_1);
            iVar3 = FUN_00407689(param_1,1,&local_e8);
            uVar5 = extraout_EDX_03;
            if (-1 < iVar3) goto LAB_00407831;
          }
          goto LAB_0040782b;
        }
      }
    }
    RegCloseKey(local_dc);
    uVar5 = extraout_EDX_02;
  }
LAB_0040782b:
  local_d8[1] = 0;
LAB_00407831:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar5);
  return;
}



/* === FUN_0040784a @ 0040784a === */

int __thiscall
FUN_0040784a(void *this,IAudioMediaType *param_1,IAudioMediaType **param_2,int param_3,int *param_4)

{
  int *piVar1;
  int *piVar2;
  IAudioMediaType *pIVar3;
  int iVar4;
  undefined4 *puVar5;
  uint local_8;
  
  local_8 = 0;
  iVar4 = FUN_00407689(this,1,&local_8);
  if (iVar4 < 0) {
    iVar4 = FUN_0040467f(this,param_1,param_2,param_4);
  }
  else {
    puVar5 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),0);
    piVar1 = (int *)*puVar5;
    puVar5 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),1);
    piVar2 = (int *)*puVar5;
    if (local_8 == *(uint *)((int)this + 0x68)) {
      iVar4 = (**(code **)(*piVar1 + 0x1c))(piVar1,param_1,param_2,param_4);
      pIVar3 = param_1;
      if (iVar4 == 0) {
        iVar4 = FUN_00402f85((int)param_1,piVar2);
        piVar1 = param_4;
        if (iVar4 == 0) {
          if (param_3 != 0) {
            FUN_0040311b((void *)((int)this + 0x4e8),0,&param_1);
            (**(code **)(*(int *)pIVar3 + 4))(pIVar3);
          }
        }
        else {
          (**(code **)(*(int *)*param_4 + 8))((int *)*param_4);
          *piVar1 = 0;
        }
      }
    }
    else {
      iVar4 = FUN_00402f85((int)param_2,piVar1);
      if (((iVar4 == 0) &&
          (iVar4 = (**(code **)(*piVar2 + 0x1c))(piVar2,param_1,param_2,param_4), iVar4 == 0)) &&
         (param_3 != 0)) {
        FUN_0040311b((void *)((int)this + 0x4e8),0,&param_2);
        (**(code **)(*param_2 + 4))(param_2);
      }
    }
  }
  return iVar4;
}



/* === FUN_0040794a @ 0040794a === */

int __thiscall FUN_0040794a(void *this,int *param_1,int *param_2,int param_3,int *param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  uint local_8;
  
  local_8 = 0;
  iVar2 = FUN_00407689(this,1,&local_8);
  if (iVar2 < 0) {
    iVar2 = FUN_004046b7(this,param_1,param_2,param_4);
    return iVar2;
  }
  puVar3 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),0);
  piVar4 = (int *)*puVar3;
  puVar3 = (undefined4 *)FUN_00403145((void *)((int)this + 0x4a4),1);
  piVar1 = (int *)*puVar3;
  if (local_8 == *(uint *)((int)this + 0x68)) {
    iVar2 = (**(code **)(*piVar4 + 0x20))(piVar4,param_1,param_2,param_4);
    if (iVar2 != 0) {
      return iVar2;
    }
    iVar2 = FUN_00402f85((int)param_2,piVar1);
    piVar4 = param_4;
    if (iVar2 != 0) {
      (**(code **)(*(int *)*param_4 + 8))((int *)*param_4);
      *piVar4 = 0;
      return iVar2;
    }
    if (param_3 == 0) {
      return 0;
    }
    FUN_0040311b((void *)((int)this + 0x4e8),0,param_4);
    piVar4 = (int *)*piVar4;
  }
  else {
    iVar2 = FUN_00402f85((int)param_1,piVar4);
    if (iVar2 != 0) {
      return iVar2;
    }
    iVar2 = (**(code **)(*piVar1 + 0x20))(piVar1,param_1,param_2,param_4);
    if (iVar2 != 0) {
      return iVar2;
    }
    if (param_3 == 0) {
      return 0;
    }
    FUN_0040311b((void *)((int)this + 0x4e8),0,&param_1);
    piVar4 = param_1;
  }
  (**(code **)(*piVar4 + 4))(piVar4);
  return 0;
}



/* === FUN_00407a41 @ 00407a41 === */

void FUN_00407a41(IAudioMediaType *param_1,IAudioMediaType *param_2,IAudioMediaType **param_3,
                 int *param_4)

{
  int iVar1;
  
  iVar1 = FUN_004076d2(param_1);
  if (iVar1 == 1) {
    FUN_0040784a(param_1,param_2,param_3,0,param_4);
    return;
  }
  FUN_0040467f(param_1,param_2,param_3,param_4);
  return;
}



/* === FUN_00407a75 @ 00407a75 === */

void FUN_00407a75(void *param_1,int *param_2,int *param_3,int *param_4)

{
  int iVar1;
  
  iVar1 = FUN_004076d2(param_1);
  if (iVar1 == 1) {
    FUN_0040794a(param_1,param_2,param_3,0,param_4);
    return;
  }
  FUN_004046b7(param_1,param_2,param_3,param_4);
  return;
}



/* === FUN_00407aa9 @ 00407aa9 === */

void FUN_00407aa9(int param_1,uint param_2,undefined4 **param_3,uint param_4,int *param_5)

{
  int *piVar1;
  LSTATUS LVar2;
  wchar_t *pwVar3;
  int iVar4;
  undefined4 *puVar5;
  HLOCAL pvVar6;
  DWORD DVar7;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar8;
  undefined4 extraout_EDX_03;
  void *pvVar9;
  char *pcVar10;
  bool bVar11;
  undefined8 uVar12;
  DWORD local_f4;
  int local_f0 [2];
  HLOCAL local_e8;
  int *local_e4;
  HKEY local_e0;
  DWORD local_dc;
  int local_d8;
  undefined4 *local_d4;
  wchar_t local_d0;
  undefined1 local_ce [198];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_e4 = param_5;
  local_d8 = param_1;
  local_dc = 100;
  local_e0 = (HKEY)0x0;
  local_d0 = L'\0';
  memset(local_ce,0,0xc6);
  if (*(int *)(param_1 + 0x488) == 2) {
    LVar2 = RegOpenKeyW((HKEY)0x80000002,L"Software\\Creative Tech\\Sound Blaster X-Fi MB",&local_e0
                       );
    if (LVar2 == 0) {
      LVar2 = RegQueryValueExW(local_e0,L"Lockid",(LPDWORD)0x0,&local_f4,(LPBYTE)&local_d0,&local_dc
                              );
      if (LVar2 == 0) {
        DVar7 = local_dc;
        pwVar3 = _wcsupr(&local_d0);
        memcpy(&local_d0,pwVar3,DVar7);
        bVar11 = true;
        DVar7 = local_dc;
        pwVar3 = &local_d0;
        pcVar10 = "F";
        do {
          if (DVar7 == 0) break;
          DVar7 = DVar7 - 1;
          bVar11 = (char)*pwVar3 == *pcVar10;
          pwVar3 = (wchar_t *)((int)pwVar3 + 1);
          pcVar10 = pcVar10 + 1;
        } while (bVar11);
        if (bVar11) {
          local_dc = 100;
          LVar2 = RegQueryValueExW(local_e0,L"UpDownMixCoExistSupport",(LPDWORD)0x0,&local_f4,
                                   (LPBYTE)local_f0,&local_dc);
          if ((LVar2 == 0) && (local_f0[0] == 1)) {
            if (*(int *)(local_d8 + 0x4d0) != 0) {
              pvVar9 = (void *)(local_d8 + -8);
              FUN_0040759f((int)pvVar9);
              iVar4 = FUN_00407689(pvVar9,1,(uint *)&local_e8);
              if (-1 < iVar4) {
                local_d4 = (undefined4 *)0x0;
                local_d4 = LocalAlloc(0x40,0x14);
                uVar8 = extraout_EDX_00;
                if (local_d4 == (undefined4 *)0x0) {
LAB_00407d12:
                  bVar11 = true;
LAB_00407d19:
                  if (bVar11) goto LAB_00407d6e;
                }
                else {
                  local_f0[1] = 0;
                  iVar4 = FUN_0040784a(pvVar9,*(IAudioMediaType **)(*local_e4 + 0xc),
                                       (IAudioMediaType **)(*param_3)[3],1,local_f0 + 1);
                  bVar11 = iVar4 < 0;
                  uVar8 = extraout_EDX_01;
                  if (iVar4 != 0) goto LAB_00407d19;
                  puVar5 = (undefined4 *)FUN_00403145((void *)(local_d8 + 0x4e0),0);
                  piVar1 = (int *)*puVar5;
                  (**(code **)(*piVar1 + 4))(piVar1);
                  iVar4 = (**(code **)(*piVar1 + 0x14))(piVar1);
                  pvVar6 = LocalAlloc(0x40,(uint)*(ushort *)(iVar4 + 2) * (*param_3)[2] * 4);
                  uVar8 = extraout_EDX_02;
                  local_e8 = pvVar6;
                  if (pvVar6 == (HLOCAL)0x0) goto LAB_00407d12;
                  FUN_0040311b((void *)(local_d8 + 0x4f0),0,&local_e8);
                  *local_d4 = **param_3;
                  local_d4[1] = pvVar6;
                  local_d4[2] = (*param_3)[2];
                  local_d4[3] = piVar1;
                  local_d4[4] = (*param_3)[4];
                }
                pvVar9 = (void *)(local_d8 + 0x4ac);
                puVar5 = (undefined4 *)FUN_00403145(pvVar9,0);
                uVar12 = (**(code **)(*(int *)*puVar5 + 0xc))
                                   ((int *)*puVar5,param_2,param_3,param_4,&local_d4);
                uVar8 = (undefined4)((ulonglong)uVar12 >> 0x20);
                if (-1 < (int)uVar12) {
                  puVar5 = (undefined4 *)FUN_00403145(pvVar9,1);
                  (**(code **)(*(int *)*puVar5 + 0xc))
                            ((int *)*puVar5,param_2,&local_d4,param_4,local_e4);
                  uVar8 = extraout_EDX_03;
                }
                goto LAB_00407d6e;
              }
            }
            goto LAB_00407c12;
          }
        }
      }
      RegCloseKey(local_e0);
    }
  }
LAB_00407c12:
  FUN_00404521(local_d8,param_2,param_3,param_4,local_e4);
  uVar8 = extraout_EDX;
LAB_00407d6e:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar8);
  return;
}



/* === FUN_00407d84 @ 00407d84 === */

void __cdecl FUN_00407d84(wchar_t *param_1,rsize_t param_2,wchar_t *param_3)

{
  errno_t eVar1;
  
  eVar1 = wcscpy_s(param_1,param_2,param_3);
  FUN_0040273a(eVar1);
  return;
}



/* === FUN_00407da7 @ 00407da7 === */

void __cdecl FUN_00407da7(wchar_t *param_1,rsize_t param_2,wchar_t *param_3,rsize_t param_4)

{
  errno_t eVar1;
  
  eVar1 = wcsncpy_s(param_1,param_2,param_3,param_4);
  FUN_0040273a(eVar1);
  return;
}



/* === FUN_00407dcd @ 00407dcd === */

void __cdecl FUN_00407dcd(wchar_t *param_1,rsize_t param_2,wchar_t *param_3)

{
  errno_t eVar1;
  
  eVar1 = wcscat_s(param_1,param_2,param_3);
  FUN_0040273a(eVar1);
  return;
}



/* === FUN_00407df0 @ 00407df0 === */

void __thiscall FUN_00407df0(void *this,undefined4 param_1)

{
  int *piVar1;
  
  for (piVar1 = *(int **)((int)this + 8); piVar1 < *(int **)((int)this + 0xc); piVar1 = piVar1 + 1)
  {
    if (*piVar1 != 0) {
      (**(code **)(*piVar1 + 0x20))(param_1);
    }
  }
  return;
}



/* === FUN_00407e1d @ 00407e1d === */

undefined4 FUN_00407e1d(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((param_2 == 1) && (DAT_0040d090 != '\0')) {
    uVar1 = 0;
  }
  return uVar1;
}



/* === FUN_00407e3e @ 00407e3e === */

int __fastcall FUN_00407e3e(int param_1)

{
  long lVar1;
  int iVar2;
  CComCriticalSection *pCVar3;
  
  pCVar3 = (CComCriticalSection *)(param_1 + 0x10);
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)pCVar3 = 0;
    pCVar3 = pCVar3 + 4;
  }
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  DAT_0040d09c = param_1;
  *(undefined4 *)(param_1 + 0x28) = 0;
  lVar1 = ATL::CComCriticalSection::Init((CComCriticalSection *)(param_1 + 0x10));
  if (lVar1 < 0) {
    DAT_0040d090 = 1;
  }
  else {
    *(undefined4 *)(param_1 + 4) = 0x24;
  }
  return param_1;
}



/* === FUN_00407e87 @ 00407e87 === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407e87(HMODULE param_1,LPCWSTR param_2,undefined4 *param_3,undefined4 *param_4)

{
  uint uVar1;
  DWORD DVar2;
  LPCWSTR lpsz;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 extraout_EDX;
  LPCWSTR pWVar6;
  LPCWSTR pWVar7;
  int local_23c;
  LPCWSTR local_238;
  LPCWSTR local_234;
  WCHAR local_230 [270];
  undefined4 local_14;
  undefined4 uStack_10;
  undefined2 uStack_c;
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_238 = param_2;
  uVar5 = 0;
  if ((param_3 == (undefined4 *)0x0) || (param_4 == (undefined4 *)0x0)) goto LAB_0040805c;
  *param_3 = 0;
  *param_4 = 0;
  local_23c = 0;
  DVar2 = GetModuleFileNameW(param_1,local_230,0x104);
  if (DVar2 == 0) {
    FUN_00402847();
  }
  else if (DVar2 != 0x104) {
    pWVar6 = (LPCWSTR)0x0;
    lpsz = local_230;
    local_234 = lpsz;
    if (local_230[0] != L'\0') {
      do {
        pWVar7 = lpsz;
        if ((local_230[0] != L'.') && (pWVar7 = pWVar6, local_230[0] == L'\\')) {
          pWVar7 = (LPCWSTR)0x0;
        }
        lpsz = CharNextW(lpsz);
        local_230[0] = *lpsz;
        pWVar6 = pWVar7;
      } while (local_230[0] != L'\0');
      local_234 = lpsz;
      if (pWVar7 != (LPCWSTR)0x0) {
        local_234 = pWVar7;
      }
    }
    if (local_238 != (LPCWSTR)0x0) {
      uVar3 = lstrlenW(local_238);
      uVar1 = uVar3 + DVar2;
      if (((uVar1 < DVar2) || (uVar1 < uVar3)) || (0x10d < uVar1)) goto LAB_00407efa;
      FUN_00407d84(local_230 + DVar2,0x10e - DVar2,local_238);
    }
    iVar4 = Ordinal_161(local_230,param_4);
    if (iVar4 < 0) {
      local_14 = _DAT_00401d70;
      iVar4 = (int)local_234 - (int)local_230 >> 1;
      uStack_10 = DAT_00401d74;
      uStack_c = DAT_00401d78;
      if (iVar4 + 5U < 0x105) {
        FUN_00407d84(local_234,0x10e - iVar4,(wchar_t *)&local_14);
        iVar4 = Ordinal_161(local_230,param_4);
        if (-1 < iVar4) goto LAB_0040802c;
      }
    }
    else {
LAB_0040802c:
      uVar5 = Ordinal_2(local_230);
      *param_3 = uVar5;
    }
  }
LAB_00407efa:
  FUN_00402fd1(&local_23c);
  uVar5 = extraout_EDX;
LAB_0040805c:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar5);
  return;
}



/* === FUN_00408072 @ 00408072 === */

void FUN_00408072(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  if (param_1 == 0) {
    RaiseException(0xc0000005,1,0,(ULONG_PTR *)0x0);
  }
  puVar2 = *(undefined4 **)(param_1 + 8);
  while (puVar2 != (undefined4 *)0x0) {
    (*(code *)*puVar2)(puVar2[1]);
    puVar1 = (undefined4 *)puVar2[2];
    FUN_00402f2f(puVar2);
    puVar2 = puVar1;
  }
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}



/* === DllCanUnloadNow @ 004080bc === */

HRESULT DllCanUnloadNow(void)

{
  int iVar1;
  
                    /* 0x80bc  1  DllCanUnloadNow */
  iVar1 = (**(code **)(DAT_0040d0d4 + 0xc))();
  return (uint)(iVar1 != 0);
}



/* === FUN_004080d5 @ 004080d5 === */

void __fastcall FUN_004080d5(int param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)(param_1 + 4);
  if (*piVar1 != 0) {
    if (*(int *)(param_1 + 0xc) != 0) {
      FUN_00408072((int)piVar1);
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
    piVar2 = *(int **)(param_1 + 0x28);
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2);
    }
    DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
    *piVar1 = 0;
  }
  return;
}



/* === FUN_00408115 @ 00408115 === */

int FUN_00408115(HMODULE param_1,LPCWSTR param_2)

{
  int iVar1;
  undefined4 local_c;
  int *local_8;
  
  local_c = 0;
  local_8 = (int *)0x0;
  iVar1 = FUN_00407e87(param_1,param_2,&local_c,&local_8);
  if (-1 < iVar1) {
    iVar1 = (**(code **)(*local_8 + 0x1c))(local_8,&param_2);
    if (-1 < iVar1) {
      iVar1 = Ordinal_186(param_2,param_2[0xc],param_2[0xd],*(undefined4 *)(param_2 + 8),
                          *(undefined4 *)(param_2 + 10));
      (**(code **)(*local_8 + 0x30))(local_8,param_2);
    }
  }
  if (local_8 != (int *)0x0) {
    (**(code **)(*local_8 + 8))(local_8);
  }
  Ordinal_6(local_c);
  return iVar1;
}



/* === FUN_0040819b @ 0040819b === */

void FUN_0040819b(HMODULE param_1,LPCWSTR param_2)

{
  WCHAR WVar1;
  LPCWSTR lpsz;
  int iVar2;
  rsize_t rVar3;
  int iVar4;
  LPWSTR pWVar5;
  uint uVar6;
  undefined4 extraout_EDX;
  LPCWSTR pWVar7;
  bool bVar8;
  WCHAR *pWVar9;
  int local_21c;
  int *local_218;
  wchar_t *local_214;
  WCHAR local_210 [260];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_214 = (wchar_t *)0x0;
  local_218 = (int *)0x0;
  iVar2 = FUN_00407e87(param_1,param_2,&local_214,&local_218);
  if (-1 < iVar2) {
    local_21c = 0;
    iVar2 = (**(code **)(*local_218 + 0x24))(local_218,0xffffffff,0,0,0,&local_21c);
    if ((iVar2 < 0) || (local_21c == 0)) {
      pWVar9 = (WCHAR *)0x0;
    }
    else {
      rVar3 = Ordinal_7(local_214);
      FUN_00407da7(local_210,0x104,local_214,rVar3);
      local_210[0x103] = 0;
      if (param_2 != (LPCWSTR)0x0) {
        iVar2 = lstrlenW(local_210);
        iVar4 = lstrlenW(param_2);
        uVar6 = iVar2 - iVar4;
        bVar8 = true;
        pWVar9 = local_210 + uVar6;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar8 = (char)*pWVar9 == (char)*param_2;
          pWVar9 = (WCHAR *)((int)pWVar9 + 1);
          param_2 = (LPCWSTR)((int)param_2 + 1);
        } while (bVar8);
        if ((bVar8) && (uVar6 < 0x104)) {
          local_210[uVar6] = L'\0';
        }
      }
      pWVar7 = local_210;
      lpsz = pWVar7;
      while (local_210[0] != L'\0') {
        pWVar5 = CharNextW(lpsz);
        WVar1 = *lpsz;
        if (((WVar1 == L'\\') || (WVar1 == L'/')) || (WVar1 == L':')) {
          pWVar7 = pWVar5;
        }
        lpsz = pWVar5;
        local_210[0] = *pWVar5;
      }
      uVar6 = (int)pWVar7 - (int)local_210 >> 1;
      if (uVar6 < 0x104) {
        local_210[uVar6] = L'\0';
      }
      pWVar9 = local_210;
    }
    Ordinal_163(local_218,local_214,pWVar9);
    Ordinal_6(local_21c);
  }
  if (local_218 != (int *)0x0) {
    (**(code **)(*local_218 + 8))(local_218);
  }
  Ordinal_6(local_214);
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,extraout_EDX);
  return;
}



/* === FUN_0040832f @ 0040832f === */

void __fastcall
FUN_0040832f(undefined4 param_1,undefined4 param_2,GUID *param_3,int *param_4,int param_5)

{
  undefined4 *puVar1;
  int iVar2;
  HRESULT HVar3;
  errno_t eVar4;
  LSTATUS LVar5;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined8 uVar6;
  int local_1ac;
  undefined4 local_1a8;
  int *local_1a4;
  int *local_1a0;
  GUID *local_19c;
  undefined4 local_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  OLECHAR local_188 [64];
  wchar_t local_108 [128];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_19c = param_3;
  local_1a4 = (int *)0x0;
  if ((param_4 != (int *)0x0) &&
     (iVar2 = _IsEqualGUIDAligned_8((int *)param_3,(int *)&DAT_00401f10), param_2 = extraout_EDX,
     iVar2 == 0)) {
    HVar3 = CoCreateInstance((IID *)&DAT_00401f00,(LPUNKNOWN)0x0,1,(IID *)&DAT_00401de8,&local_1a4);
    param_2 = extraout_EDX_00;
    if (HVar3 < 0) {
      if (local_1a4 != (int *)0x0) {
        (**(code **)(*local_1a4 + 8))(local_1a4);
        param_2 = extraout_EDX_01;
      }
    }
    else {
      iVar2 = *param_4;
      local_1a0 = param_4;
      while (iVar2 != 0) {
        puVar1 = (undefined4 *)local_1a0[1];
        local_198 = *puVar1;
        uStack_194 = puVar1[1];
        uStack_190 = puVar1[2];
        uStack_18c = puVar1[3];
        if (param_5 == 0) {
          if (*local_1a0 == 1) {
            (**(code **)(*local_1a4 + 0x18))();
            param_2 = extraout_EDX_05;
          }
          else {
            (**(code **)(*local_1a4 + 0x20))(local_1a4,local_19c,1,&local_198);
            param_2 = extraout_EDX_06;
          }
        }
        else {
          if (*local_1a0 == 1) {
            uVar6 = (**(code **)(*local_1a4 + 0x14))();
          }
          else {
            uVar6 = (**(code **)(*local_1a4 + 0x1c))(local_1a4);
          }
          param_2 = (undefined4)((ulonglong)uVar6 >> 0x20);
          if ((int)uVar6 < 0) {
            if (local_1a4 != (int *)0x0) {
              (**(code **)(*local_1a4 + 8))(local_1a4);
              param_2 = extraout_EDX_04;
            }
            goto LAB_00408585;
          }
        }
        local_1a0 = local_1a0 + 2;
        iVar2 = *local_1a0;
      }
      if (param_5 == 0) {
        StringFromGUID2(local_19c,local_188,0x40);
        local_1ac = 0;
        eVar4 = wcscpy_s(local_108,0x80,L"CLSID\\");
        FUN_0040273a(eVar4);
        FUN_00407dcd(local_108,0x80,local_188);
        eVar4 = wcscat_s(local_108,0x80,L"\\Required Categories");
        FUN_0040273a(eVar4);
        local_1a8 = 0x80000000;
        local_19c = (GUID *)0x0;
        local_1a0 = (int *)0x0;
        iVar2 = FUN_00402983(&local_19c,(HKEY)0x80000000,local_108,0x20019);
        if (iVar2 == 0) {
          LVar5 = RegQueryInfoKeyW((HKEY)local_19c,(LPWSTR)0x0,(LPDWORD)0x0,(LPDWORD)0x0,
                                   (LPDWORD)&local_1a0,(LPDWORD)0x0,(LPDWORD)0x0,(LPDWORD)0x0,
                                   (LPDWORD)0x0,(LPDWORD)0x0,(LPDWORD)0x0,(PFILETIME)0x0);
          ATL::CRegKey::Close((CRegKey *)&local_19c);
          if ((LVar5 == 0) && (local_1a0 == (int *)0x0)) {
            RegDeleteKeyW((HKEY)0x80000000,local_108);
          }
        }
        eVar4 = wcscpy_s(local_108,0x80,L"CLSID\\");
        FUN_0040273a(eVar4);
        FUN_00407dcd(local_108,0x80,local_188);
        eVar4 = wcscat_s(local_108,0x80,L"\\Implemented Categories");
        FUN_0040273a(eVar4);
        iVar2 = FUN_00402983(&local_19c,(HKEY)0x80000000,local_108,0x20019);
        if (iVar2 == 0) {
          LVar5 = RegQueryInfoKeyW((HKEY)local_19c,(LPWSTR)0x0,(LPDWORD)0x0,(LPDWORD)0x0,
                                   (LPDWORD)&local_1a0,(LPDWORD)0x0,(LPDWORD)0x0,(LPDWORD)0x0,
                                   (LPDWORD)0x0,(LPDWORD)0x0,(LPDWORD)0x0,(PFILETIME)0x0);
          ATL::CRegKey::Close((CRegKey *)&local_19c);
          if ((LVar5 == 0) && (local_1a0 == (int *)0x0)) {
            RegDeleteKeyW((HKEY)0x80000000,local_108);
          }
        }
        ATL::CRegKey::Close((CRegKey *)&local_19c);
        ATL::CRegKey::Close((CRegKey *)&local_1a8);
        FUN_00402fd1(&local_1ac);
        param_2 = extraout_EDX_02;
      }
      if (local_1a4 != (int *)0x0) {
        (**(code **)(*local_1a4 + 8))(local_1a4);
        param_2 = extraout_EDX_03;
      }
    }
  }
LAB_00408585:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,param_2);
  return;
}



/* === FUN_0040861d @ 0040861d === */

int * FUN_0040861d(int *param_1,int *param_2,undefined4 param_3,int *param_4)

{
  undefined4 *puVar1;
  int iVar2;
  LPCRITICAL_SECTION lpCriticalSection;
  int *piVar3;
  
  if (param_1 == (int *)0x0) {
    param_1 = (int *)0x80070057;
  }
  else if (*param_1 == 0) {
    param_1 = (int *)0x8000ffff;
  }
  else if (param_4 == (int *)0x0) {
    param_1 = (int *)0x80004003;
  }
  else {
    *param_4 = 0;
    for (piVar3 = (int *)param_1[2]; piVar3 < (int *)param_1[3]; piVar3 = piVar3 + 1) {
      puVar1 = (undefined4 *)*piVar3;
      if (((puVar1 != (undefined4 *)0x0) && (puVar1[2] != 0)) &&
         (iVar2 = _IsEqualGUIDAligned_8(param_2,(int *)*puVar1), iVar2 != 0)) {
        piVar3 = puVar1 + 4;
        if (*piVar3 == 0) {
          lpCriticalSection = (LPCRITICAL_SECTION)(param_1 + 4);
          EnterCriticalSection(lpCriticalSection);
          param_1 = (int *)0x0;
          if (*piVar3 == 0) {
            param_1 = (int *)(*(code *)puVar1[2])(puVar1[3],&DAT_00401780,piVar3);
          }
          LeaveCriticalSection(lpCriticalSection);
          if (*piVar3 != 0) goto LAB_004086bb;
        }
        else {
LAB_004086bb:
          param_1 = (int *)(*(code *)**(undefined4 **)*piVar3)
                                     ((undefined4 *)*piVar3,param_3,param_4);
        }
        if (*param_4 != 0) {
          return param_1;
        }
        if (param_1 != (int *)0x0) {
          return param_1;
        }
        break;
      }
    }
    param_1 = (int *)0x80040111;
  }
  return param_1;
}



/* === FUN_004086ef @ 004086ef === */

void FUN_004086ef(undefined4 param_1,int param_2)

{
  FUN_00407e1d(&DAT_0040d0d4,param_2);
  return;
}



/* === FUN_0040870d @ 0040870d === */

void FUN_0040870d(int *param_1,undefined4 param_2,int *param_3)

{
  FUN_0040861d(&DAT_0040d17c,param_1,param_2,param_3);
  return;
}



/* === FUN_0040872e @ 0040872e === */

int __fastcall FUN_0040872e(int param_1)

{
  FUN_00407e3e(param_1);
  DAT_0040d0a0 = DAT_00401cec;
  DAT_0040d0a4 = DAT_00401cf0;
  DAT_0040d0a8 = DAT_00401cf4;
  DAT_0040d0ac = DAT_00401cf8;
  return param_1;
}



/* === FUN_00408753 @ 00408753 === */

int FUN_00408753(int param_1,int param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 *puVar3;
  int *piVar4;
  int *piVar5;
  bool bVar6;
  undefined8 uVar7;
  int iVar8;
  int local_c;
  
  if (param_1 == 0) {
    iVar2 = -0x7ff8ffa9;
  }
  else {
    puVar3 = *(undefined4 **)(param_1 + 8);
    local_c = 0;
    iVar2 = 0;
    if (puVar3 < *(undefined4 **)(param_1 + 0xc)) {
      do {
        puVar1 = (undefined4 *)*puVar3;
        if (puVar1 != (undefined4 *)0x0) {
          if (param_3 != (int *)0x0) {
            iVar2 = 4;
            bVar6 = true;
            piVar4 = param_3;
            piVar5 = (int *)*puVar1;
            do {
              if (iVar2 == 0) break;
              iVar2 = iVar2 + -1;
              bVar6 = *piVar4 == *piVar5;
              piVar4 = piVar4 + 1;
              piVar5 = piVar5 + 1;
            } while (bVar6);
            if (!bVar6) goto LAB_004087b8;
          }
          iVar8 = 1;
          iVar2 = (*(code *)puVar1[1])();
          if (iVar2 < 0) {
            return iVar2;
          }
          uVar7 = (*(code *)puVar1[7])(1);
          local_c = FUN_0040832f(extraout_ECX,(int)((ulonglong)uVar7 >> 0x20),(GUID *)*puVar1,
                                 (int *)uVar7,iVar8);
          if (local_c < 0) {
            return local_c;
          }
        }
LAB_004087b8:
        puVar3 = puVar3 + 1;
      } while (puVar3 < *(undefined4 **)(param_1 + 0xc));
      iVar2 = local_c;
      if (local_c < 0) {
        return local_c;
      }
    }
    if (param_2 != 0) {
      iVar2 = FUN_0040819b(*(HMODULE *)(param_1 + 4),(LPCWSTR)0x0);
    }
  }
  return iVar2;
}



/* === FUN_004087e6 @ 004087e6 === */

int FUN_004087e6(int param_1,int param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 *puVar3;
  int *piVar4;
  int *piVar5;
  bool bVar6;
  undefined8 uVar7;
  int local_c;
  
  if (param_1 == 0) {
    iVar2 = -0x7ff8ffa9;
  }
  else {
    puVar3 = *(undefined4 **)(param_1 + 8);
    local_c = 0;
    iVar2 = 0;
    if (puVar3 < *(undefined4 **)(param_1 + 0xc)) {
      do {
        puVar1 = (undefined4 *)*puVar3;
        if (puVar1 != (undefined4 *)0x0) {
          if (param_3 != (int *)0x0) {
            iVar2 = 4;
            bVar6 = true;
            piVar4 = param_3;
            piVar5 = (int *)*puVar1;
            do {
              if (iVar2 == 0) break;
              iVar2 = iVar2 + -1;
              bVar6 = *piVar4 == *piVar5;
              piVar4 = piVar4 + 1;
              piVar5 = piVar5 + 1;
            } while (bVar6);
            if (!bVar6) goto LAB_0040884b;
          }
          iVar2 = 0;
          uVar7 = (*(code *)puVar1[7])();
          iVar2 = FUN_0040832f(extraout_ECX,(int)((ulonglong)uVar7 >> 0x20),(GUID *)*puVar1,
                               (int *)uVar7,iVar2);
          if (iVar2 < 0) {
            return iVar2;
          }
          local_c = (*(code *)puVar1[1])(0);
          if (local_c < 0) {
            return local_c;
          }
        }
LAB_0040884b:
        puVar3 = puVar3 + 1;
      } while (puVar3 < *(undefined4 **)(param_1 + 0xc));
      iVar2 = local_c;
      if (local_c < 0) {
        return local_c;
      }
    }
    if (param_2 != 0) {
      iVar2 = FUN_00408115(*(HMODULE *)(param_1 + 4),(LPCWSTR)0x0);
    }
  }
  return iVar2;
}



/* === FUN_00408879 @ 00408879 === */

int __fastcall FUN_00408879(int param_1)

{
  FUN_0040872e(param_1);
  FUN_00407df0(&DAT_0040d17c,1);
  return param_1;
}



/* === FUN_00408898 @ 00408898 === */

void __fastcall FUN_00408898(int param_1)

{
  FUN_00407df0(&DAT_0040d17c,0);
  FUN_004080d5(param_1);
  return;
}



/* === FUN_004088df @ 004088df === */

HRESULT __thiscall FUN_004088df(void *this,undefined4 *param_1)

{
  LPVOID *ppv;
  HRESULT HVar1;
  
  HVar1 = 0;
  if (param_1 == (undefined4 *)0x0) {
    HVar1 = -0x7fffbffd;
  }
  else {
    ppv = (LPVOID *)((int)this + 0x28);
    if ((*ppv != (LPVOID)0x0) ||
       (HVar1 = CoCreateInstance((IID *)&DAT_0040132c,(LPUNKNOWN)0x0,1,(IID *)&DAT_00401e10,ppv),
       -1 < HVar1)) {
      *param_1 = *ppv;
      (**(code **)(*(int *)*ppv + 4))(*ppv);
    }
  }
  return HVar1;
}



/* === FUN_00408932 @ 00408932 === */

void FUN_00408932(int *param_1)

{
  (**(code **)(*param_1 + 0xc))(param_1,L"APPID",L"{B4BC7D22-B40A-42ba-BE9A-690B0AF9C48D}");
  return;
}



/* === FUN_00408953 @ 00408953 === */

HLOCAL __thiscall FUN_00408953(void *this,byte param_1)

{
  FUN_00408898((int)this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === DllGetClassObject @ 00408979 === */

HRESULT DllGetClassObject(IID *rclsid,IID *riid,LPVOID *ppv)

{
  HRESULT HVar1;
  
                    /* 0x8979  2  DllGetClassObject */
  HVar1 = FUN_0040870d((int *)rclsid,riid,(int *)ppv);
  return HVar1;
}



/* === FUN_0040898e @ 0040898e === */

void FUN_0040898e(int param_1,int *param_2)

{
  int iVar1;
  
  if ((DAT_0040d098 != (code *)0x0) && (iVar1 = (*DAT_0040d098)(), iVar1 < 0)) {
    return;
  }
  FUN_004087e6(0x40d17c,param_1,param_2);
  return;
}



/* === FUN_004089bb @ 004089bb === */

void FUN_004089bb(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = FUN_00408753(0x40d17c,param_1,param_2);
  if ((-1 < iVar1) && (DAT_0040d094 != (code *)0x0)) {
    (*DAT_0040d094)(DAT_0040d118);
  }
  return;
}



/* === FUN_004089ef @ 004089ef === */

void FUN_004089ef(int param_1)

{
  wchar_t *local_14;
  wchar_t *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  local_8 = 0;
  local_14 = L"APPID";
  local_10 = L"{B4BC7D22-B40A-42ba-BE9A-690B0AF9C48D}";
  FUN_00406966(DAT_0040d09c,0x65,param_1,&local_14);
  return;
}



/* === DllUnregisterServer @ 00408a2a === */

void DllUnregisterServer(void)

{
                    /* 0x8a2a  4  DllUnregisterServer */
  FUN_0040898e(1,(int *)0x0);
  return;
}



/* === FUN_00408a3e @ 00408a3e === */

int FUN_00408a3e(int param_1)

{
  LCID Locale;
  int iVar1;
  
  Locale = GetThreadLocale();
  SetThreadLocale(0x800);
  iVar1 = FUN_004089ef(1);
  if (-1 < iVar1) {
    iVar1 = FUN_004089bb(param_1,(int *)0x0);
  }
  SetThreadLocale(Locale);
  return iVar1;
}



/* === FUN_00408a8d @ 00408a8d === */

int __fastcall FUN_00408a8d(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 extraout_ECX;
  uint uVar2;
  uint uVar3;
  undefined8 uVar4;
  
  uVar2 = 0;
  do {
    uVar4 = FUN_0040a26d(param_1,param_2,(GUID *)(&PTR_DAT_0040d058)[uVar2]);
    param_2 = (undefined4)((ulonglong)uVar4 >> 0x20);
    iVar1 = (int)uVar4;
    if (iVar1 < 0) goto LAB_00408ac1;
    uVar2 = uVar2 + 1;
    param_1 = extraout_ECX;
  } while (uVar2 < 2);
  iVar1 = FUN_00408a3e(param_3);
  if (iVar1 < 0) {
LAB_00408ac1:
    uVar3 = 0;
    if (uVar2 != 0) {
      do {
        FUN_0040a134((GUID *)(&PTR_DAT_0040d058)[uVar3]);
        uVar3 = uVar3 + 1;
      } while (uVar3 < uVar2);
    }
  }
  return iVar1;
}



/* === DllRegisterServer @ 00408ae6 === */

void __fastcall DllRegisterServer(undefined4 param_1,undefined4 param_2)

{
                    /* 0x8ae6  3  DllRegisterServer */
  FUN_00408a8d(&DAT_0040d0d4,param_2,1);
  return;
}



/* === AtlWinModuleInit @ 00408af8 === */

/* Library Function - Single Match
    long __stdcall ATL::AtlWinModuleInit(struct ATL::_ATL_WIN_MODULE70 *)
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

long ATL::AtlWinModuleInit(_ATL_WIN_MODULE70 *param_1)

{
  long lVar1;
  
  if ((param_1 == (_ATL_WIN_MODULE70 *)0x0) || (*(int *)param_1 != 0x2c)) {
    lVar1 = -0x7ff8ffa9;
  }
  else {
    *(undefined4 *)(param_1 + 0x1c) = 0;
    lVar1 = CComCriticalSection::Init((CComCriticalSection *)(param_1 + 4));
  }
  return lVar1;
}



/* === RemoveAll @ 00408b25 === */

/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall ATL::CSimpleArray<unsigned short,class
   ATL::CSimpleArrayEqualHelper<unsigned short> >::RemoveAll(void)
    public: void __thiscall ATL::CSimpleArray<unsigned long,class
   ATL::CSimpleArrayEqualHelper<unsigned long> >::RemoveAll(void)
    public: void __thiscall ATL::CSimpleArray<struct HINSTANCE__ *,class
   ATL::CSimpleArrayEqualHelper<struct HINSTANCE__ *> >::RemoveAll(void)
    public: void __thiscall ATL::CSimpleArray<class CDHtmlControlSink *,class
   ATL::CSimpleArrayEqualHelper<class CDHtmlControlSink *> >::RemoveAll(void)
     6 names - too many to list
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release, Visual Studio 2008 Release,
   Visual Studio 2010 Release */

void __fastcall RemoveAll(undefined4 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    free((void *)*param_1);
    *param_1 = 0;
  }
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}



/* === FUN_00408b49 @ 00408b49 === */

int __thiscall FUN_00408b49(void *this,int param_1)

{
  code *pcVar1;
  int iVar2;
  
  if ((-1 < param_1) && (param_1 < *(int *)((int)this + 4))) {
    return *(int *)this + param_1 * 2;
  }
  RaiseException(0xc000008c,1,0,(ULONG_PTR *)0x0);
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}



/* === FUN_00408b7a @ 00408b7a === */

int __fastcall FUN_00408b7a(int param_1)

{
  FUN_004027c7((undefined4 *)(param_1 + 4));
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  return param_1;
}



/* === AtlWinModuleTerm @ 00408b9b === */

/* Library Function - Single Match
    long __stdcall ATL::AtlWinModuleTerm(struct ATL::_ATL_WIN_MODULE70 *,struct HINSTANCE__ *)
   
   Library: Visual Studio 2008 Release */

long ATL::AtlWinModuleTerm(_ATL_WIN_MODULE70 *param_1,HINSTANCE__ *param_2)

{
  long lVar1;
  ushort *puVar2;
  int iVar3;
  
  iVar3 = 0;
  if (param_1 == (_ATL_WIN_MODULE70 *)0x0) {
LAB_00408bab:
    lVar1 = -0x7ff8ffa9;
  }
  else {
    if (*(int *)param_1 != 0) {
      if (*(int *)param_1 != 0x2c) goto LAB_00408bab;
      if (0 < *(int *)(param_1 + 0x24)) {
        do {
          puVar2 = (ushort *)FUN_00408b49(param_1 + 0x20,iVar3);
          UnregisterClassA((LPCSTR)(uint)*puVar2,param_2);
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(param_1 + 0x24));
      }
      RemoveAll((undefined4 *)(param_1 + 0x20));
      DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 4));
      *(undefined4 *)param_1 = 0;
    }
    lVar1 = 0;
  }
  return lVar1;
}



/* === FUN_00408c04 @ 00408c04 === */

int __fastcall FUN_00408c04(int param_1)

{
  FUN_004027c7((undefined4 *)(param_1 + 0x18));
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  return param_1;
}



/* === FUN_00408c42 @ 00408c42 === */

_ATL_WIN_MODULE70 * __fastcall FUN_00408c42(_ATL_WIN_MODULE70 *param_1)

{
  long lVar1;
  
  FUN_00408b7a((int)param_1);
  *(undefined4 *)param_1 = 0x2c;
  lVar1 = ATL::AtlWinModuleInit(param_1);
  if (lVar1 < 0) {
    DAT_0040d090 = 1;
    *(undefined4 *)param_1 = 0;
  }
  return param_1;
}



/* === FUN_00408c6f @ 00408c6f === */

void __fastcall FUN_00408c6f(undefined4 *param_1)

{
  long lVar1;
  undefined4 extraout_EDX;
  _OSVERSIONINFOA local_9c;
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  FUN_00408c04((int)param_1);
  param_1[2] = 0x400000;
  param_1[1] = 0x400000;
  *param_1 = 0x3c;
  *(undefined1 *)(param_1 + 3) = 0;
  memset(&local_9c,0,0x94);
  local_9c.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_9c);
  if (local_9c.dwPlatformId == 2) {
    if (local_9c.dwMajorVersion < 5) goto LAB_00408d03;
  }
  else if ((local_9c.dwPlatformId != 1) ||
          ((local_9c.dwMajorVersion < 5 &&
           ((local_9c.dwMajorVersion != 4 || (local_9c.dwMinorVersion == 0)))))) goto LAB_00408d03;
  *(undefined1 *)(param_1 + 3) = 1;
LAB_00408d03:
  param_1[4] = 0x800;
  param_1[5] = &DAT_00401e5c;
  lVar1 = ATL::CComCriticalSection::Init((CComCriticalSection *)(param_1 + 6));
  if (lVar1 < 0) {
    DAT_0040d090 = 1;
  }
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,extraout_EDX);
  return;
}



/* === FUN_00408da0 @ 00408da0 === */

undefined4 * __fastcall FUN_00408da0(undefined4 *param_1)

{
  long lVar1;
  
  FUN_004027c7(param_1 + 4);
  *param_1 = 0;
  param_1[1] = 0x400000;
  param_1[2] = &PTR_PTR_0040b080;
  param_1[3] = &DAT_0040b088;
  lVar1 = ATL::CComCriticalSection::Init((CComCriticalSection *)(param_1 + 4));
  if (lVar1 < 0) {
    DAT_0040d090 = 1;
  }
  else {
    *param_1 = 0x28;
  }
  return param_1;
}



/* === ___CppXcptFilter @ 00408dec === */

/* Library Function - Single Match
    ___CppXcptFilter
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release */

int __cdecl ___CppXcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr)

{
  int iVar1;
  
  if (_ExceptionNum == 0xe06d7363) {
    iVar1 = _XcptFilter(0xe06d7363,_ExceptionPtr);
    return iVar1;
  }
  return 0;
}



/* === __initterm_e @ 00408e11 === */

/* Library Function - Single Match
    __initterm_e
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release */

void __cdecl __initterm_e(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while ((param_1 < param_2 && (iVar1 == 0))) {
    if ((code *)*param_1 != (code *)0x0) {
      iVar1 = (*(code *)*param_1)();
    }
    param_1 = param_1 + 1;
  }
  return;
}



/* === FUN_00408e61 @ 00408e61 === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00408e61(undefined4 param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  undefined4 *_Memory;
  LONG LVar2;
  int iVar3;
  BOOL BVar4;
  undefined4 *puVar5;
  
  if (param_2 == 0) {
    if (DAT_0040d1dc < 1) {
      return 0;
    }
    DAT_0040d1dc = DAT_0040d1dc + -1;
  }
  _DAT_0040d508 = *(undefined4 *)_adjust_fdiv_exref;
  if (param_2 == 1) {
    iVar3 = *(int *)((int)Self + 4);
    bVar1 = false;
    while (LVar2 = InterlockedCompareExchange((LONG *)&DAT_0040d510,iVar3,0), LVar2 != 0) {
      if (LVar2 == iVar3) {
        bVar1 = true;
        break;
      }
      Sleep(1000);
    }
    if (DAT_0040d50c == 0) {
      DAT_0040d50c = 1;
      iVar3 = __initterm_e((undefined4 *)&DAT_004011a8,(undefined4 *)&DAT_004011b0);
      if (iVar3 != 0) {
        return 0;
      }
      initterm(&LAB_00401180,&DAT_004011a4);
      DAT_0040d50c = 2;
    }
    else {
      _amsg_exit(0x1f);
    }
    if (!bVar1) {
      InterlockedExchange((LONG *)&DAT_0040d510,0);
    }
    if ((DAT_0040d520 != (code *)0x0) &&
       (BVar4 = __IsNonwritableInCurrentImage((PBYTE)&DAT_0040d520), BVar4 != 0)) {
      (*DAT_0040d520)(param_1,2,param_3);
    }
    DAT_0040d1dc = DAT_0040d1dc + 1;
  }
  else if (param_2 == 0) {
    while (LVar2 = InterlockedCompareExchange((LONG *)&DAT_0040d510,1,0), _Memory = DAT_0040d518,
          LVar2 != 0) {
      Sleep(1000);
    }
    if (DAT_0040d50c == 2) {
      puVar5 = DAT_0040d514;
      if (DAT_0040d518 != (undefined4 *)0x0) {
        while (puVar5 = puVar5 + -1, _Memory <= puVar5) {
          if ((code *)*puVar5 != (code *)0x0) {
            (*(code *)*puVar5)();
          }
        }
        free(_Memory);
        DAT_0040d514 = (undefined4 *)0x0;
        DAT_0040d518 = (undefined4 *)0x0;
      }
      DAT_0040d50c = 0;
      InterlockedExchange((LONG *)&DAT_0040d510,0);
    }
    else {
      _amsg_exit(0x1f);
    }
  }
  return 1;
}



/* === FUN_00409007 @ 00409007 === */

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00409007(undefined4 param_1,int param_2,undefined4 param_3)

{
  int local_20;
  
  local_20 = 1;
  _DAT_0040d080 = param_2;
  if ((param_2 == 0) && (DAT_0040d1dc == 0)) {
    local_20 = 0;
  }
  else {
    if ((param_2 == 1) || (param_2 == 2)) {
      if (DAT_0040d51c != (code *)0x0) {
        local_20 = (*DAT_0040d51c)(param_1,param_2,param_3);
      }
      if ((local_20 == 0) || (local_20 = FUN_00408e61(param_1,param_2,param_3), local_20 == 0))
      goto LAB_00409234;
    }
    local_20 = FUN_004086ef(param_1,param_2);
    if ((param_2 == 1) && (local_20 == 0)) {
      FUN_004086ef(param_1,0);
      FUN_00408e61(param_1,0,0);
      if (DAT_0040d51c != (code *)0x0) {
        (*DAT_0040d51c)(param_1,0,0);
      }
    }
    if ((((param_2 == 0) || (param_2 == 3)) &&
        (local_20 = FUN_00408e61(param_1,param_2,param_3), local_20 != 0)) &&
       (DAT_0040d51c != (code *)0x0)) {
      local_20 = (*DAT_0040d51c)(param_1,param_2,param_3);
    }
  }
LAB_00409234:
  FUN_0040924b();
  return local_20;
}



/* === FUN_0040924b @ 0040924b === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040924b(void)

{
  _DAT_0040d080 = 0xffffffff;
  return;
}



/* === entry @ 0040925b === */

void entry(undefined4 param_1,int param_2,undefined4 param_3)

{
  if (param_2 == 1) {
    FUN_00409663();
  }
  FUN_00409007(param_1,param_2,param_3);
  return;
}



/* === free @ 00409276 === */

void __cdecl free(void *_Memory)

{
                    /* WARNING: Could not recover jumptable at 0x00409276. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(_Memory);
  return;
}



/* === memcpy_s @ 00409282 === */

errno_t __cdecl memcpy_s(void *_Dst,rsize_t _DstSize,void *_Src,rsize_t _MaxCount)

{
  errno_t eVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00409282. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  eVar1 = memcpy_s(_Dst,_DstSize,_Src,_MaxCount);
  return eVar1;
}



/* === memmove_s @ 0040928e === */

errno_t __cdecl memmove_s(void *_Dst,rsize_t _DstSize,void *_Src,rsize_t _MaxCount)

{
  errno_t eVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040928e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  eVar1 = memmove_s(_Dst,_DstSize,_Src,_MaxCount);
  return eVar1;
}



/* === wcsncpy_s @ 0040929a === */

errno_t __cdecl wcsncpy_s(wchar_t *_Dst,rsize_t _SizeInWords,wchar_t *_Src,rsize_t _MaxCount)

{
  errno_t eVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040929a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  eVar1 = wcsncpy_s(_Dst,_SizeInWords,_Src,_MaxCount);
  return eVar1;
}



/* === __SEH_prolog4 @ 004092a8 === */

/* WARNING: This is an inlined function */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Variable defined which should be unmapped: param_2 */
/* Library Function - Single Match
    __SEH_prolog4
   
   Library: Visual Studio */

void __cdecl __SEH_prolog4(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 unaff_retaddr;
  uint auStack_1c [5];
  undefined1 local_8 [8];
  
  iVar1 = -param_2;
  *(undefined4 *)((int)auStack_1c + iVar1 + 0x10) = unaff_EBX;
  *(undefined4 *)((int)auStack_1c + iVar1 + 0xc) = unaff_ESI;
  *(undefined4 *)((int)auStack_1c + iVar1 + 8) = unaff_EDI;
  *(uint *)((int)auStack_1c + iVar1 + 4) = DAT_0040d060 ^ (uint)&param_2;
  *(undefined4 *)((int)auStack_1c + iVar1) = unaff_retaddr;
  ExceptionList = local_8;
  return;
}



/* === __SEH_epilog4 @ 004092ed === */

/* WARNING: This is an inlined function */
/* Library Function - Single Match
    __SEH_epilog4
   
   Library: Visual Studio */

void __SEH_epilog4(void)

{
  undefined4 *unaff_EBP;
  undefined4 unaff_retaddr;
  
  ExceptionList = (void *)unaff_EBP[-4];
  *unaff_EBP = unaff_retaddr;
  return;
}



/* === FUN_00409306 @ 00409306 === */

void __cdecl
FUN_00409306(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  except_handler4_common(&DAT_0040d060,FUN_00409330,param_1,param_2,param_3,param_4);
  return;
}



/* === FUN_00409330 @ 00409330 === */

void __fastcall FUN_00409330(int param_1,undefined4 param_2)

{
  if (param_1 == DAT_0040d060) {
    return;
  }
  FUN_004096f9(param_1,param_2);
  return;
}



/* === __alloca_probe @ 00409350 === */

/* WARNING: This is an inlined function */
/* Library Function - Single Match
    __chkstk
   
   Library: Visual Studio */

void __alloca_probe(void)

{
  undefined1 *in_EAX;
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 unaff_retaddr;
  undefined1 auStack_4 [4];
  
  puVar2 = (undefined4 *)((int)&stack0x00000000 - (int)in_EAX & ~-(uint)(&stack0x00000000 < in_EAX))
  ;
  for (puVar1 = (undefined4 *)((uint)auStack_4 & 0xfffff000); puVar2 < puVar1;
      puVar1 = puVar1 + -0x400) {
  }
  *puVar2 = unaff_retaddr;
  return;
}



/* === memcpy @ 0040938c === */

void * __cdecl memcpy(void *_Dst,void *_Src,size_t _Size)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040938c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memcpy(_Dst,_Src,_Size);
  return pvVar1;
}



/* === FUN_00409397 @ 00409397 === */

void * __cdecl FUN_00409397(void *param_1,uint param_2,uint param_3)

{
  int *piVar1;
  void *pvVar2;
  
  if ((param_2 == 0) || (param_3 <= 0xffffffe0 / param_2)) {
    pvVar2 = realloc(param_1,param_2 * param_3);
  }
  else {
    piVar1 = _errno();
    *piVar1 = 0xc;
    FUN_00409896();
    pvVar2 = (void *)0x0;
  }
  return pvVar2;
}



/* === memset @ 004093e6 === */

void * __cdecl memset(void *_Dst,int _Val,size_t _Size)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004093e6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memset(_Dst,_Val,_Size);
  return pvVar1;
}



/* === wcscpy_s @ 004093f2 === */

errno_t __cdecl wcscpy_s(wchar_t *_Dst,rsize_t _SizeInWords,wchar_t *_Src)

{
  errno_t eVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004093f2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  eVar1 = wcscpy_s(_Dst,_SizeInWords,_Src);
  return eVar1;
}



/* === wcscat_s @ 004093fe === */

errno_t __cdecl wcscat_s(wchar_t *_Dst,rsize_t _SizeInWords,wchar_t *_Src)

{
  errno_t eVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004093fe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  eVar1 = wcscat_s(_Dst,_SizeInWords,_Src);
  return eVar1;
}



/* === FUN_00409409 @ 00409409 === */

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */

_onexit_t __cdecl FUN_00409409(_onexit_t param_1)

{
  _onexit_t p_Var1;
  undefined4 local_24;
  int local_20 [5];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0040b040;
  uStack_c = 0x409415;
  local_20[0] = DAT_0040d518;
  if (DAT_0040d518 == -1) {
    p_Var1 = _onexit(param_1);
  }
  else {
    _lock(8);
    local_8 = (undefined *)0x0;
    local_20[0] = DAT_0040d518;
    local_24 = DAT_0040d514;
    p_Var1 = (_onexit_t)__dllonexit(param_1,local_20,&local_24);
    DAT_0040d518 = local_20[0];
    DAT_0040d514 = local_24;
    local_8 = (undefined *)0xfffffffe;
    FUN_00409485();
  }
  return p_Var1;
}



/* === FUN_00409485 @ 00409485 === */

void FUN_00409485(void)

{
  _unlock(8);
  return;
}



/* === FUN_00409493 @ 00409493 === */

int __cdecl FUN_00409493(_onexit_t param_1)

{
  _onexit_t p_Var1;
  
  p_Var1 = FUN_00409409(param_1);
  return (p_Var1 != (_onexit_t)0x0) - 1;
}



/* === __alloca_probe_16 @ 00409510 === */

/* WARNING: This is an inlined function */
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* Library Function - Single Match
    __alloca_probe_16
   
   Library: Visual Studio */

uint __alloca_probe_16(void)

{
  uint in_EAX;
  uint uVar1;
  
  uVar1 = 4 - in_EAX & 0xf;
  return in_EAX + uVar1 | -(uint)CARRY4(in_EAX,uVar1);
}



/* === __alloca_probe_8 @ 00409526 === */

/* WARNING: This is an inlined function */
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* Library Function - Single Match
    __alloca_probe_8
   
   Library: Visual Studio */

uint __alloca_probe_8(void)

{
  uint in_EAX;
  uint uVar1;
  
  uVar1 = 4 - in_EAX & 7;
  return in_EAX + uVar1 | -(uint)CARRY4(in_EAX,uVar1);
}



/* === _XcptFilter @ 00409542 === */

int __cdecl _XcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00409542. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = _XcptFilter(_ExceptionNum,_ExceptionPtr);
  return iVar1;
}



/* === FUN_00409550 @ 00409550 === */

bool __cdecl FUN_00409550(short *param_1)

{
  if ((*param_1 == 0x5a4d) && (*(int *)(*(int *)(param_1 + 0x1e) + (int)param_1) == 0x4550)) {
    return (short)((int *)(*(int *)(param_1 + 0x1e) + (int)param_1))[6] == 0x10b;
  }
  return false;
}



/* === FUN_00409590 @ 00409590 === */

int __cdecl FUN_00409590(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(param_1 + 0x3c) + param_1;
  uVar3 = 0;
  iVar1 = *(ushort *)(iVar2 + 0x14) + 0x18 + iVar2;
  if (*(ushort *)(iVar2 + 6) != 0) {
    do {
      if ((*(uint *)(iVar1 + 0xc) <= param_2) &&
         (param_2 < *(int *)(iVar1 + 8) + *(uint *)(iVar1 + 0xc))) {
        return iVar1;
      }
      uVar3 = uVar3 + 1;
      iVar1 = iVar1 + 0x28;
    } while (uVar3 < *(ushort *)(iVar2 + 6));
  }
  return 0;
}



/* === __IsNonwritableInCurrentImage @ 004095db === */

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __IsNonwritableInCurrentImage
   
   Library: Visual Studio 2005 Release */

BOOL __cdecl __IsNonwritableInCurrentImage(PBYTE pTarget)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  int extraout_EDX;
  
  bVar1 = FUN_00409550((short *)&IMAGE_DOS_HEADER_00400000);
  if ((CONCAT31(extraout_var,bVar1) != 0) &&
     (iVar2 = FUN_00409590(extraout_EDX,(int)pTarget - extraout_EDX), iVar2 != 0)) {
    return ~(*(uint *)(iVar2 + 0x24) >> 0x1f) & 1;
  }
  return 0;
}



/* === initterm @ 0040964c === */

void __cdecl initterm(void)

{
                    /* WARNING: Could not recover jumptable at 0x0040964c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  initterm();
  return;
}



/* === _amsg_exit @ 00409658 === */

void __cdecl _amsg_exit(int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00409658. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _amsg_exit(param_1);
  return;
}



/* === FUN_00409663 @ 00409663 === */

void FUN_00409663(void)

{
  DWORD DVar1;
  DWORD DVar2;
  DWORD DVar3;
  uint uVar4;
  LARGE_INTEGER local_14;
  _FILETIME local_c;
  
  local_c.dwLowDateTime = 0;
  local_c.dwHighDateTime = 0;
  if ((DAT_0040d060 == 0xbb40e64e) || ((DAT_0040d060 & 0xffff0000) == 0)) {
    GetSystemTimeAsFileTime(&local_c);
    uVar4 = local_c.dwHighDateTime ^ local_c.dwLowDateTime;
    DVar1 = GetCurrentProcessId();
    DVar2 = GetCurrentThreadId();
    DVar3 = GetTickCount();
    QueryPerformanceCounter(&local_14);
    DAT_0040d060 = uVar4 ^ DVar1 ^ DVar2 ^ DVar3 ^ local_14.s.HighPart ^ local_14.s.LowPart;
    if (DAT_0040d060 == 0xbb40e64e) {
      DAT_0040d060 = 0xbb40e64f;
    }
  }
  DAT_0040d064 = ~DAT_0040d060;
  return;
}



/* === except_handler4_common @ 004096ee === */

void __cdecl except_handler4_common(void)

{
                    /* WARNING: Could not recover jumptable at 0x004096ee. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  except_handler4_common();
  return;
}



/* === FUN_004096f9 @ 004096f9 === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004096f9(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  HANDLE hProcess;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined2 in_ES;
  undefined2 in_CS;
  undefined2 in_SS;
  undefined2 in_DS;
  undefined2 in_FS;
  undefined2 in_GS;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  undefined4 unaff_retaddr;
  UINT uExitCode;
  undefined4 local_32c;
  undefined4 local_328;
  
  _DAT_0040d2f0 =
       (uint)(in_NT & 1) * 0x4000 | (uint)SBORROW4((int)&stack0xfffffffc,0x328) * 0x800 |
       (uint)(in_IF & 1) * 0x200 | (uint)(in_TF & 1) * 0x100 | (uint)((int)&local_32c < 0) * 0x80 |
       (uint)(&stack0x00000000 == (undefined1 *)0x32c) * 0x40 | (uint)(in_AF & 1) * 0x10 |
       (uint)((POPCOUNT((uint)&local_32c & 0xff) & 1U) == 0) * 4 |
       (uint)(&stack0xfffffffc < (undefined1 *)0x328) | (uint)(in_ID & 1) * 0x200000 |
       (uint)(in_VIP & 1) * 0x100000 | (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000;
  _DAT_0040d2f4 = &stack0x00000004;
  _DAT_0040d230 = 0x10001;
  _DAT_0040d1e0 = 0xc0000409;
  _DAT_0040d1e4 = 1;
  local_32c = DAT_0040d060;
  local_328 = DAT_0040d064;
  _DAT_0040d1ec = unaff_retaddr;
  _DAT_0040d2bc = in_GS;
  _DAT_0040d2c0 = in_FS;
  _DAT_0040d2c4 = in_ES;
  _DAT_0040d2c8 = in_DS;
  _DAT_0040d2cc = unaff_EDI;
  _DAT_0040d2d0 = unaff_ESI;
  _DAT_0040d2d4 = unaff_EBX;
  _DAT_0040d2d8 = param_2;
  _DAT_0040d2dc = param_1;
  _DAT_0040d2e0 = in_EAX;
  _DAT_0040d2e4 = unaff_EBP;
  DAT_0040d2e8 = unaff_retaddr;
  _DAT_0040d2ec = in_CS;
  _DAT_0040d2f8 = in_SS;
  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)0x0);
  UnhandledExceptionFilter((_EXCEPTION_POINTERS *)&PTR_DAT_00401ec4);
  uExitCode = 0xc0000409;
  hProcess = GetCurrentProcess();
  TerminateProcess(hProcess,uExitCode);
  return;
}



/* === realloc @ 004097e0 === */

void * __cdecl realloc(void *_Memory,size_t _NewSize)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004097e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = realloc(_Memory,_NewSize);
  return pvVar1;
}



/* === FUN_004097eb @ 004097eb === */

void FUN_004097eb(void)

{
  uint uVar1;
  undefined4 extraout_EDX;
  
  uVar1 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  OutputDebugStringA("Invalid parameter passed to C runtime function.\n");
  FUN_00409330(uVar1 ^ (uint)&stack0xfffffffc,extraout_EDX);
  return;
}



/* === FUN_00409896 @ 00409896 === */

void FUN_00409896(void)

{
  FUN_004097eb();
  return;
}



/* === _errno @ 004098a6 === */

int * __cdecl _errno(void)

{
  int *piVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004098a6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  piVar1 = _errno();
  return piVar1;
}



/* === _unlock @ 004098b2 === */

void __cdecl _unlock(int _File)

{
                    /* WARNING: Could not recover jumptable at 0x004098b2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _unlock(_File);
  return;
}



/* === __dllonexit @ 004098be === */

void __dllonexit(void)

{
                    /* WARNING: Could not recover jumptable at 0x004098be. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  __dllonexit();
  return;
}



/* === _lock @ 004098ca === */

void __cdecl _lock(int _File)

{
                    /* WARNING: Could not recover jumptable at 0x004098ca. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _lock(_File);
  return;
}



/* === FUN_004098d5 @ 004098d5 === */

undefined4 __fastcall FUN_004098d5(int param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  bVar1 = (byte)*(undefined4 *)(*(int *)(param_1 + 0x10) + 0x10);
  uVar2 = 0;
  if (((((bVar1 & 2) == 2) && (*(int *)(param_2 + 0x10) != *(int *)(param_1 + 0x2c))) ||
      (((bVar1 & 8) == 8 &&
       ((*(int *)(param_2 + 0x18) != *(int *)(param_1 + 0x34) ||
        (*(int *)(param_2 + 0x14) != *(int *)(param_1 + 0x30))))))) ||
     (((bVar1 & 4) == 4 && (*(float *)(param_1 + 0x38) != *(float *)(param_2 + 0x1c))))) {
    uVar2 = 0x887d0009;
  }
  return uVar2;
}



/* === FUN_0040993a @ 0040993a === */

void __fastcall
FUN_0040993a(undefined4 param_1,undefined4 param_2,uint param_3,int param_4,uint param_5,int param_6
            )

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  uint local_58;
  undefined1 local_50 [16];
  int local_40;
  int local_3c;
  undefined1 local_2c [16];
  int local_1c;
  int local_18;
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  bVar5 = false;
  local_58 = 0;
  if (param_3 != 0) {
    do {
      if (bVar5) break;
      piVar1 = (int *)(param_4 + local_58 * 4);
      iVar2 = *piVar1;
      uVar7 = 0;
      if (*(int *)(iVar2 + 4) != 0) {
        if (*(int *)(iVar2 + 0xc) == 0) break;
        uVar9 = (**(code **)(**(int **)(iVar2 + 0xc) + 0x18))(*(int **)(iVar2 + 0xc),local_2c);
        param_2 = (undefined4)((ulonglong)uVar9 >> 0x20);
        if ((int)uVar9 < 0) break;
        iVar2 = *piVar1;
        uVar3 = *(uint *)(iVar2 + 4);
        uVar8 = *(int *)(iVar2 + 8) * local_18 * local_1c + uVar3;
        if (param_5 != 0) {
          do {
            if (bVar5) break;
            iVar2 = *(int *)(param_6 + uVar7 * 4);
            if (*(int *)(iVar2 + 4) != 0) {
              if (*(int *)(iVar2 + 0xc) == 0) goto LAB_00409a39;
              uVar9 = (**(code **)(**(int **)(iVar2 + 0xc) + 0x18))(*(int **)(iVar2 + 0xc),local_50)
              ;
              param_2 = (undefined4)((ulonglong)uVar9 >> 0x20);
              if ((int)uVar9 < 0) goto LAB_00409a39;
              iVar2 = *(int *)(param_6 + uVar7 * 4);
              uVar4 = *(uint *)(iVar2 + 4);
              uVar6 = *(int *)(iVar2 + 8) * local_3c * local_40 + uVar4;
              if ((((uVar3 < uVar4) || (uVar6 <= uVar3)) && ((uVar8 <= uVar4 || (uVar6 < uVar8))))
                 && ((uVar4 <= uVar3 || (uVar8 <= uVar6)))) {
                bVar5 = false;
              }
              else {
                bVar5 = true;
              }
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 < param_5);
        }
      }
      local_58 = local_58 + 1;
    } while (local_58 < param_3);
  }
LAB_00409a39:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,param_2);
  return;
}



/* === FUN_00409a4f @ 00409a4f === */

void FUN_00409a4f(int param_1,uint param_2,int *param_3,uint param_4,int *param_5)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  uint extraout_EDX;
  uint extraout_EDX_00;
  undefined4 extraout_EDX_01;
  int *piVar6;
  undefined8 uVar7;
  uint local_3c;
  int *local_34;
  uint local_30;
  undefined1 local_2c [16];
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  local_34 = (int *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0xc));
  if ((((*(char *)(param_1 + 4) != '\0') ||
       ((param_2 != 0 && ((param_3 == (int *)0x0 || (*param_3 == 0)))))) ||
      ((param_4 != 0 && ((param_5 == (int *)0x0 || (*param_5 == 0)))))) ||
     (((((param_2 & 0x3fffffff) != 0 && (param_3 == (int *)0x0)) ||
       (((((param_4 & 0x3fffffff) != 0 && (param_5 == (int *)0x0)) ||
         (iVar4 = *(int *)(param_1 + 8), param_2 < *(uint *)(iVar4 + 0x41c))) ||
        ((*(uint *)(iVar4 + 0x420) < param_2 || (param_4 < *(uint *)(iVar4 + 0x424))))))) ||
      (*(uint *)(iVar4 + 0x428) < param_4)))) goto LAB_00409d80;
  if (param_2 == 0) {
    if (param_4 != 0) {
      iVar4 = *param_5;
      goto LAB_00409b23;
    }
  }
  else {
    iVar4 = *param_3;
LAB_00409b23:
    if ((*(int *)(iVar4 + 0xc) == 0) ||
       (iVar4 = (**(code **)(**(int **)(iVar4 + 0xc) + 0x18))(*(int **)(iVar4 + 0xc),local_2c),
       iVar4 < 0)) goto LAB_00409d80;
    iVar4 = *(int *)(param_1 + 8);
    if (((byte)*(undefined4 *)(iVar4 + 0x10) & 2) == 2) {
      *(undefined4 *)(param_1 + 0x24) = local_1c;
    }
    if (((byte)*(undefined4 *)(iVar4 + 0x10) & 8) == 8) {
      *(undefined4 *)(param_1 + 0x2c) = local_14;
      *(undefined4 *)(param_1 + 0x28) = local_18;
    }
    if (((byte)*(undefined4 *)(iVar4 + 0x10) & 4) == 4) {
      *(undefined4 *)(param_1 + 0x30) = local_10;
    }
  }
  local_30 = 0;
  uVar5 = param_2;
  piVar6 = param_3;
  if (param_2 != 0) {
    do {
      local_3c = 0;
      if (param_4 != 0) {
        piVar1 = (int *)(param_1 + -8);
        do {
          if (local_34 != (int *)0x0) {
            (**(code **)(*local_34 + 8))(local_34);
            local_34 = (int *)0x0;
          }
          iVar4 = (**(code **)(*piVar1 + 0x20))
                            (piVar1,*(undefined4 *)(*piVar6 + 0xc),
                             *(undefined4 *)(param_5[local_3c] + 0xc),&local_34);
          if (iVar4 != 0) goto LAB_00409d80;
          if (local_34 != (int *)0x0) {
            (**(code **)(*local_34 + 8))(local_34);
            local_34 = (int *)0x0;
          }
          uVar7 = (**(code **)(*piVar1 + 0x1c))
                            (piVar1,*(undefined4 *)(param_5[local_3c] + 0xc),
                             *(undefined4 *)(*piVar6 + 0xc),&local_34);
          uVar5 = (uint)((ulonglong)uVar7 >> 0x20);
          if ((int)uVar7 != 0) goto LAB_00409d80;
          local_3c = local_3c + 1;
        } while (local_3c < param_4);
      }
      local_30 = local_30 + 1;
      piVar6 = piVar6 + 1;
    } while (local_30 < param_2);
  }
  local_30 = 0;
  if (param_2 != 0) {
    do {
      iVar4 = param_3[local_30];
      if ((((*(int *)(iVar4 + 0x10) != 0x41434453) || (*(int *)(iVar4 + 0xc) == 0)) ||
          (iVar4 = (**(code **)(**(int **)(iVar4 + 0xc) + 0x18))(*(int **)(iVar4 + 0xc),local_2c),
          iVar4 < 0)) || (iVar4 = FUN_004098d5(param_1 + -8,(int)local_2c), iVar4 < 0))
      goto LAB_00409d80;
      local_30 = local_30 + 1;
      uVar5 = extraout_EDX;
    } while (local_30 < param_2);
  }
  local_30 = 0;
  if (param_4 != 0) {
    do {
      iVar4 = param_5[local_30];
      if (((*(int *)(iVar4 + 0x10) != 0x41434453) || (*(int *)(iVar4 + 0xc) == 0)) ||
         ((iVar4 = (**(code **)(**(int **)(iVar4 + 0xc) + 0x18))(*(int **)(iVar4 + 0xc),local_2c),
          iVar4 < 0 || (iVar4 = FUN_004098d5(param_1 + -8,(int)local_2c), iVar4 < 0))))
      goto LAB_00409d80;
      local_30 = local_30 + 1;
      uVar5 = extraout_EDX_00;
    } while (local_30 < param_4);
  }
  if ((((param_2 == 0) || (param_4 == 0)) ||
      (((bVar2 = (byte)*(undefined4 *)(*(int *)(param_1 + 8) + 0x10), (bVar2 & 4) != 4 ||
        (uVar5 = *(uint *)(*param_3 + 8), uVar5 <= *(uint *)(*param_5 + 8))) &&
       (((bVar2 & 1) == 1 ||
        (cVar3 = FUN_0040993a(param_1 + -8,uVar5,param_2,(int)param_3,param_4,(int)param_5),
        cVar3 == '\0')))))) &&
     (iVar4 = (**(code **)(*(int *)(param_1 + -8) + 0x2c))(param_2,param_3,param_4,param_5),
     -1 < iVar4)) {
    *(undefined1 *)(param_1 + 4) = 1;
  }
LAB_00409d80:
  if (local_34 != (int *)0x0) {
    (**(code **)(*local_34 + 8))(local_34);
    local_34 = (int *)0x0;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0xc));
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,extraout_EDX_01);
  return;
}



/* === UnlockForProcess @ 00409db2 === */

/* Library Function - Single Match
    public: virtual long __stdcall CBaseAudioProcessingObject::UnlockForProcess(void)
   
   Library: Visual Studio 2012 Release */

long CBaseAudioProcessingObject::UnlockForProcess(void)

{
  long lVar1;
  int in_stack_00000004;
  
  lVar1 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)(in_stack_00000004 + 0xc));
  if (*(char *)(in_stack_00000004 + 4) == '\0') {
    lVar1 = -0x7782fffa;
  }
  else {
    *(undefined1 *)(in_stack_00000004 + 4) = 0;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(in_stack_00000004 + 0xc));
  return lVar1;
}



/* === FUN_00409ded @ 00409ded === */

undefined4 FUN_00409ded(void)

{
  return 0;
}



/* === FUN_00409df7 @ 00409df7 === */

undefined4 FUN_00409df7(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_2 = 0;
    param_2[1] = 0;
  }
  return uVar1;
}



/* === FUN_00409e1a @ 00409e1a === */

undefined4 FUN_00409e1a(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*(char *)(param_1 + 0xd) == '\0') {
    uVar1 = 0x887d0002;
  }
  else if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_2 = *(undefined4 *)(param_1 + 0x2c);
  }
  return uVar1;
}



/* === FUN_00409e4c @ 00409e4c === */

undefined4 FUN_00409e4c(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  LPVOID _Dst;
  SIZE_T cb;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    cb = (*(int *)(*(int *)(param_1 + 0x10) + 0x430) + -1) * 0x10 + 0x444;
    _Dst = CoTaskMemAlloc(cb);
    if (_Dst == (LPVOID)0x0) {
      uVar1 = 0x8007000e;
    }
    else {
      memcpy(_Dst,*(void **)(param_1 + 0x10),cb);
      *param_2 = _Dst;
      uVar1 = 0;
    }
  }
  return uVar1;
}



/* === FUN_00409eab @ 00409eab === */

void __fastcall FUN_00409eab(int param_1)

{
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x14));
  return;
}



/* === FUN_00409ebb @ 00409ebb === */

void __thiscall FUN_00409ebb(void *this,int *param_1,int *param_2,undefined4 *param_3)

{
  int iVar1;
  int extraout_ECX;
  int iVar2;
  undefined4 extraout_EDX;
  undefined4 uVar3;
  int iVar4;
  undefined8 uVar5;
  undefined1 local_50 [16];
  int local_40;
  int local_3c;
  int local_38;
  float local_34;
  undefined4 local_30;
  int local_2c [4];
  int local_1c;
  int local_18;
  int local_14;
  float local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  if (param_1 != (int *)0x0) {
    uVar5 = (**(code **)(*param_1 + 0x18))(param_1,local_50);
    uVar3 = (undefined4)((ulonglong)uVar5 >> 0x20);
    if ((int)uVar5 < 0) goto LAB_00409fd2;
    uVar5 = (**(code **)(*(int *)this + 0x30))(1);
    uVar3 = (undefined4)((ulonglong)uVar5 >> 0x20);
    if (((int)uVar5 == 1) || ((int)uVar5 < 0)) goto LAB_00409fd2;
  }
  uVar5 = (**(code **)(*param_2 + 0x18))(param_2,local_2c);
  uVar3 = (undefined4)((ulonglong)uVar5 >> 0x20);
  if (-1 < (int)uVar5) {
    uVar5 = (**(code **)(*(int *)this + 0x30))(0);
    uVar3 = (undefined4)((ulonglong)uVar5 >> 0x20);
    iVar4 = (int)uVar5;
    if (-1 < iVar4) {
      iVar2 = extraout_ECX;
      if (param_1 != (int *)0x0) {
        iVar1 = *(int *)((int)this + 0x10);
        if (((*(byte *)(iVar1 + 0x10) & 2) != 0) && (local_1c != local_40)) {
          local_1c = local_40;
          local_c = local_30;
          iVar4 = 1;
        }
        iVar2 = extraout_ECX;
        if (((*(byte *)(iVar1 + 0x10) & 8) != 0) &&
           ((iVar2 = local_3c, local_14 != local_38 || (local_18 != local_3c)))) {
          local_14 = local_38;
          local_18 = local_3c;
          iVar4 = 1;
        }
        if (((*(byte *)(iVar1 + 0x10) & 4) != 0) && (local_34 != local_10)) {
          local_10 = local_34;
          iVar4 = 1;
        }
      }
      if (iVar4 == 0) {
        *param_3 = param_2;
        (**(code **)(*param_2 + 4))(param_2);
        uVar3 = extraout_EDX;
      }
      else {
        uVar5 = FUN_0040ad3e(iVar2,uVar3,local_2c,param_3);
        uVar3 = (undefined4)((ulonglong)uVar5 >> 0x20);
      }
    }
  }
LAB_00409fd2:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar3);
  return;
}



/* === FUN_00409fea @ 00409fea === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __fastcall FUN_00409fea(undefined4 param_1,int *param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  bool bVar9;
  bool bVar10;
  
  iVar6 = 4;
  bVar9 = true;
  piVar7 = &DAT_00401f28;
  piVar8 = param_2;
  do {
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    bVar9 = *piVar7 == *piVar8;
    piVar7 = piVar7 + 1;
    piVar8 = piVar8 + 1;
  } while (bVar9);
  if (!bVar9) {
    *param_2 = DAT_00401f28;
    param_2[1] = DAT_00401f2c;
    param_2[2] = DAT_00401f30;
    param_2[3] = DAT_00401f34;
  }
  puVar1 = (uint *)(param_2 + 4);
  uVar2 = *puVar1;
  if (uVar2 == 0) {
    *puVar1 = 1;
  }
  uVar3 = *puVar1;
  if (0x1000 < uVar3) {
    *puVar1 = 0x1000;
  }
  iVar6 = param_2[5];
  if (iVar6 != 4) {
    param_2[5] = 4;
  }
  iVar4 = param_2[6];
  if (iVar4 != 0x20) {
    param_2[6] = 0x20;
  }
  bVar10 = (float)param_2[7] < _DAT_00401f24;
  if (bVar10) {
    param_2[7] = (int)_DAT_00401f24;
  }
  bVar5 = _DAT_00401f20 < (float)param_2[7];
  if (bVar5) {
    param_2[7] = (int)_DAT_00401f20;
  }
  return bVar5 || (bVar10 ||
                  (iVar4 != 0x20 || (iVar6 != 4 || (0x1000 < uVar3 || (uVar2 == 0 || !bVar9)))));
}



/* === IsInputFormatSupported @ 0040a08d === */

/* Library Function - Single Match
    public: virtual long __stdcall CBaseAudioProcessingObject::IsInputFormatSupported(struct
   IAudioMediaType *,struct IAudioMediaType *,struct IAudioMediaType * *)
   
   Libraries: Visual Studio 2012 Release, Visual Studio 2015 Release, Visual Studio 2017 Release,
   Visual Studio 2019 Release */

long CBaseAudioProcessingObject::IsInputFormatSupported
               (IAudioMediaType *param_1,IAudioMediaType *param_2,IAudioMediaType **param_3)

{
  long lVar1;
  undefined4 *in_stack_00000010;
  
  if ((param_3 == (IAudioMediaType **)0x0) || (in_stack_00000010 == (undefined4 *)0x0)) {
    lVar1 = -0x7fffbffd;
  }
  else {
    *in_stack_00000010 = 0;
    lVar1 = FUN_00409ebb(param_1,(int *)param_2,(int *)param_3,in_stack_00000010);
  }
  return lVar1;
}



/* === FUN_0040a0c3 @ 0040a0c3 === */

undefined4 FUN_0040a0c3(void *param_1,int *param_2,int *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  if ((param_3 == (int *)0x0) || (param_4 == (undefined4 *)0x0)) {
    uVar1 = 0x80004003;
  }
  else {
    *param_4 = 0;
    uVar1 = FUN_00409ebb(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}



/* === FUN_0040a0f8 @ 0040a0f8 === */

int __thiscall FUN_0040a0f8(void *this,undefined4 param_1)

{
  *(undefined4 *)((int)this + 0x10) = param_1;
  *(undefined1 *)((int)this + 0xc) = 0;
  *(undefined1 *)((int)this + 0xd) = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)((int)this + 0x14));
  *(undefined4 *)((int)this + 0x2c) = 0;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x30) = 0;
  *(undefined4 *)((int)this + 0x34) = 0;
  return (int)this;
}



/* === FUN_0040a134 @ 0040a134 === */

void FUN_0040a134(GUID *param_1)

{
  LSTATUS LVar1;
  int iVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  HKEY local_40c;
  OLECHAR local_408 [512];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  LVar1 = RegOpenKeyExW((HKEY)0x80000000,L"AudioEngine\\AudioProcessingObjects",0,0x20006,&local_40c
                       );
  uVar3 = extraout_EDX;
  if (LVar1 == 0) {
    iVar2 = StringFromGUID2(param_1,local_408,0x200);
    if (iVar2 != 0) {
      RegDeleteKeyW(local_40c,local_408);
    }
    RegCloseKey(local_40c);
    uVar3 = extraout_EDX_00;
  }
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,uVar3);
  return;
}



/* === FUN_0040a1e1 @ 0040a1e1 === */

undefined4 FUN_0040a1e1(int *param_1,undefined4 *param_2)

{
  int *piVar1;
  undefined4 uVar2;
  
  piVar1 = (int *)*param_1;
  uVar2 = 0;
  if (piVar1 != (int *)0x0) {
    *param_1 = *piVar1;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = piVar1[2];
    }
    uVar2 = 1;
  }
  return uVar2;
}



/* === FUN_0040a20b @ 0040a20b === */

int __cdecl FUN_0040a20b(wchar_t *param_1,uint param_2,wchar_t *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = param_2 >> 1;
  iVar1 = 0;
  if ((uVar3 == 0) || (0x7fffffff < uVar3)) {
    iVar1 = -0x7ff8ffa9;
  }
  if (-1 < iVar1) {
    uVar3 = uVar3 - 1;
    iVar1 = 0;
    uVar2 = _vsnwprintf(param_1,uVar3,param_3,&stack0x00000010);
    if (((int)uVar2 < 0) || (uVar3 < uVar2)) {
      param_1[uVar3] = L'\0';
      iVar1 = -0x7ff8ff86;
    }
    else if (uVar2 == uVar3) {
      param_1[uVar3] = L'\0';
    }
  }
  return iVar1;
}



/* === FUN_0040a26d @ 0040a26d === */

void __fastcall FUN_0040a26d(undefined4 param_1,undefined4 param_2,GUID *param_3)

{
  uint uVar1;
  ushort uVar2;
  GUID *pGVar3;
  LSTATUS LVar4;
  int iVar5;
  ushort *puVar6;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  HKEY local_818;
  undefined4 *local_814;
  GUID *local_810;
  HKEY local_80c;
  wchar_t local_808 [512];
  OLECHAR local_408 [512];
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  if ((param_3 != (GUID *)0x0) &&
     (LVar4 = RegCreateKeyExW((HKEY)0x80000000,L"AudioEngine\\AudioProcessingObjects",0,(LPWSTR)0x0,
                              0,0x20006,(LPSECURITY_ATTRIBUTES)0x0,&local_818,(LPDWORD)0x0),
     param_2 = extraout_EDX, LVar4 == 0)) {
    iVar5 = StringFromGUID2(param_3,local_408,0x200);
    if (iVar5 != 0) {
      RegDeleteKeyW(local_818,local_408);
      LVar4 = RegCreateKeyExW(local_818,local_408,0,(LPWSTR)0x0,0,0x20006,(LPSECURITY_ATTRIBUTES)0x0
                              ,&local_80c,(LPDWORD)0x0);
      if (LVar4 == 0) {
        puVar6 = &param_3[1].Data2;
        do {
          uVar2 = *puVar6;
          puVar6 = puVar6 + 1;
        } while (uVar2 != 0);
        uVar1 = ((int)puVar6 - (int)&param_3[1].Data3 >> 1) * 2 + 2;
        if (uVar1 < 0x201) {
          LVar4 = RegSetValueExW(local_80c,L"FriendlyName",0,1,(BYTE *)&param_3[1].Data2,uVar1);
          if (LVar4 == 0) {
            local_810 = (GUID *)&param_3[0x21].Data3;
            puVar6 = &param_3[0x21].Data2;
            do {
              uVar2 = *puVar6;
              puVar6 = puVar6 + 1;
            } while (uVar2 != 0);
            uVar1 = ((int)puVar6 - (int)local_810 >> 1) * 2 + 2;
            if ((((((uVar1 < 0x201) &&
                   (LVar4 = RegSetValueExW(local_80c,L"Copyright",0,1,(BYTE *)&param_3[0x21].Data2,
                                           uVar1), LVar4 == 0)) &&
                  (LVar4 = RegSetValueExW(local_80c,L"MajorVersion",0,4,(BYTE *)&param_3[0x41].Data2
                                          ,4), LVar4 == 0)) &&
                 (((LVar4 = RegSetValueExW(local_80c,L"MinorVersion",0,4,param_3[0x41].Data4,4),
                   LVar4 == 0 &&
                   (LVar4 = RegSetValueExW(local_80c,L"Flags",0,4,(BYTE *)(param_3 + 1),4),
                   LVar4 == 0)) &&
                  ((LVar4 = RegSetValueExW(local_80c,L"MinInputConnections",0,4,
                                           param_3[0x41].Data4 + 4,4), LVar4 == 0 &&
                   ((LVar4 = RegSetValueExW(local_80c,L"MaxInputConnections",0,4,
                                            (BYTE *)(param_3 + 0x42),4), LVar4 == 0 &&
                    (LVar4 = RegSetValueExW(local_80c,L"MinOutputConnections",0,4,
                                            (BYTE *)&param_3[0x42].Data2,4), LVar4 == 0)))))))) &&
                (LVar4 = RegSetValueExW(local_80c,L"MaxOutputConnections",0,4,param_3[0x42].Data4,4)
                , LVar4 == 0)) &&
               ((LVar4 = RegSetValueExW(local_80c,L"MaxInstances",0,4,param_3[0x42].Data4 + 4,4),
                LVar4 == 0 &&
                (LVar4 = RegSetValueExW(local_80c,L"NumAPOInterfaces",0,4,(BYTE *)(param_3 + 0x43),4
                                       ), LVar4 == 0)))) {
              local_814 = (undefined4 *)0x0;
              pGVar3 = DAT_0040d4fc;
              if (param_3[0x43].Data1 != 0) {
                local_810 = (GUID *)&param_3[0x43].Data2;
                do {
                  iVar5 = FUN_0040a20b(local_808,0x400,L"APOInterface%u");
                  param_2 = extraout_EDX_00;
                  if (iVar5 < 0) goto LAB_0040a602;
                  iVar5 = StringFromGUID2(local_810,local_408,0x200);
                  if (((iVar5 == 0) || (0x400 < (uint)(iVar5 * 2))) ||
                     (LVar4 = RegSetValueExW(local_80c,local_808,0,1,(BYTE *)local_408,iVar5 * 2),
                     LVar4 != 0)) goto LAB_0040a5e9;
                  local_814 = (undefined4 *)((int)local_814 + 1);
                  local_810 = local_810 + 1;
                  pGVar3 = DAT_0040d4fc;
                } while (local_814 < (undefined4 *)param_3[0x43].Data1);
              }
              while (local_810 = pGVar3, local_810 != (GUID *)0x0) {
                iVar5 = FUN_0040a1e1((int *)&local_810,&local_814);
                pGVar3 = local_810;
                if (iVar5 != 0) {
                  SetEvent((HANDLE)*local_814);
                  pGVar3 = local_810;
                }
              }
              local_810 = (GUID *)0x0;
            }
          }
LAB_0040a5e9:
          RegCloseKey(local_80c);
        }
      }
    }
    RegCloseKey(local_818);
    param_2 = extraout_EDX_01;
  }
LAB_0040a602:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,param_2);
  return;
}



/* === FUN_0040a630 @ 0040a630 === */

undefined4 FUN_0040a630(uint param_1,int param_2,uint *param_3)

{
  undefined4 uVar1;
  
  if (param_2 + param_1 < param_1) {
    *param_3 = 0xffffffff;
    uVar1 = 0x80070216;
  }
  else {
    *param_3 = param_2 + param_1;
    uVar1 = 0;
  }
  return uVar1;
}



/* === ~CAudioMediaType @ 0040a65e === */

/* Library Function - Single Match
    protected: virtual __thiscall CAudioMediaType::~CAudioMediaType(void)
   
   Libraries: Visual Studio 2012 Release, Visual Studio 2015 Release, Visual Studio 2017 Release,
   Visual Studio 2019 Release */

void __thiscall CAudioMediaType::~CAudioMediaType(CAudioMediaType *this)

{
  *(undefined ***)this = &PTR_FUN_0040211c;
  FUN_00402f2f(*(HLOCAL *)(this + 0xc));
  *(undefined4 *)(this + 0xc) = 0;
  return;
}



/* === FUN_0040a67d @ 0040a67d === */

undefined4 FUN_0040a67d(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80070057;
  }
  else {
    *param_2 = *(undefined4 *)(param_1 + 8);
  }
  return uVar1;
}



/* === Release @ 0040a6a3 === */

/* Library Function - Multiple Matches With Same Base Name
    public: virtual unsigned long __stdcall CEnumMediaTypes::Release(void)
    public: virtual unsigned long __stdcall CEnumPins::Release(void)
   
   Library: Visual Studio 2019 Release */

LONG Release(int *param_1)

{
  LONG LVar1;
  
  LVar1 = InterlockedDecrement(param_1 + 1);
  if ((LVar1 == 0) && (param_1 != (int *)0x0)) {
    (**(code **)(*param_1 + 0x1c))(1);
  }
  return LVar1;
}



/* === FUN_0040a6d7 @ 0040a6d7 === */

undefined4 FUN_0040a6d7(int *param_1,int *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int *piVar4;
  bool bVar5;
  
  uVar2 = 0;
  if (param_3 == (undefined4 *)0x0) {
    uVar2 = 0x80070057;
  }
  else {
    iVar1 = 4;
    bVar5 = true;
    *param_3 = 0;
    piVar3 = param_2;
    piVar4 = &DAT_0040213c;
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar5 = *piVar3 == *piVar4;
      piVar3 = piVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (bVar5);
    if (!bVar5) {
      iVar1 = 4;
      bVar5 = true;
      piVar3 = &DAT_00401780;
      do {
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        bVar5 = *param_2 == *piVar3;
        param_2 = param_2 + 1;
        piVar3 = piVar3 + 1;
      } while (bVar5);
      if (!bVar5) {
        return 0x80004002;
      }
    }
    *param_3 = param_1;
    (**(code **)(*param_1 + 4))(param_1);
  }
  return uVar2;
}



/* === FUN_0040a733 @ 0040a733 === */

uint FUN_0040a733(int *param_1,int *param_2,uint *param_3)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  int iVar7;
  short *psVar8;
  char *pcVar9;
  bool bVar10;
  undefined4 local_2c;
  uint local_28;
  uint local_24;
  undefined4 local_20;
  short local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  short local_8;
  
  if ((param_2 == (int *)0x0) || (param_3 == (uint *)0x0)) {
    return 0x80070057;
  }
  *param_3 = 0;
  if (param_1 == param_2) {
    *param_3 = 0xe;
  }
  else {
    puVar2 = (uint *)(**(code **)(*param_2 + 0x14))(param_2);
    if (puVar2 != (uint *)0x0) {
      puVar6 = (uint *)param_1[3];
      if (puVar6 != (uint *)0x0) {
        local_18 = *puVar6;
        uVar1 = local_18;
        local_14 = puVar6[1];
        local_10 = puVar6[2];
        local_c = puVar6[3];
        local_8 = (short)puVar6[4];
        local_2c = *puVar2;
        local_28 = puVar2[1];
        local_24 = puVar2[2];
        local_20 = puVar2[3];
        local_1c = (short)puVar2[4];
        if ((short)(local_18 >> 0x10) == 0) {
          local_2c = *puVar2 & 0xffff;
          local_24 = 0;
          local_20 = puVar2[3] & 0xffff0000;
        }
        if (puVar6[1] == 0) {
          local_28 = 0;
          local_24 = 0;
        }
        if ((short)(local_c >> 0x10) == 0) {
          local_20 = 0;
        }
        if ((short)local_18 == 0) {
          local_2c = local_2c & 0xffff0000;
        }
        local_18 = uVar1;
        if (local_2c._2_2_ == 0) {
          local_18 = local_18 & 0xffff;
          local_10 = 0;
          local_c = local_c & 0xffff0000;
        }
        if (local_28 == 0) {
          local_14 = 0;
          local_10 = 0;
        }
        if (local_20._2_2_ == 0) {
          local_c = 0;
        }
        if ((short)local_2c == 0) {
          local_18 = local_18 & 0xffff0000;
        }
        if ((short)local_2c == 1) {
          local_1c = 0;
        }
        if ((short)local_18 == 1) {
          local_8 = 0;
        }
        if ((short)local_2c != (short)local_18) {
          return 1;
        }
        if ((short)*puVar6 == -2) {
          iVar3 = 4;
          bVar10 = true;
          puVar5 = puVar2 + 6;
          puVar6 = puVar6 + 6;
          do {
            if (iVar3 == 0) break;
            iVar3 = iVar3 + -1;
            bVar10 = *puVar5 == *puVar6;
            puVar5 = puVar5 + 1;
            puVar6 = puVar6 + 1;
          } while (bVar10);
          if (!bVar10) {
            return 1;
          }
        }
        if (local_1c != local_8) {
          return 1;
        }
        *param_3 = *param_3 | 2;
        uVar1 = *param_3;
        iVar3 = 9;
        bVar10 = true;
        puVar6 = &local_18;
        psVar8 = (short *)&local_2c;
        do {
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          bVar10 = (short)*puVar6 == *psVar8;
          puVar6 = (uint *)((int)puVar6 + 2);
          psVar8 = psVar8 + 1;
        } while (bVar10);
        if (!bVar10) {
          return 1;
        }
        *param_3 = uVar1 | 4;
        psVar8 = (short *)param_1[3];
        iVar3 = 0x12;
        iVar7 = iVar3;
        if (*psVar8 != 1) {
          iVar7 = (ushort)psVar8[8] + 0x12;
        }
        if ((short)*puVar2 != 1) {
          iVar3 = (ushort)puVar2[4] + 0x12;
        }
        if (iVar7 == iVar3) {
          uVar4 = (uint)(ushort)puVar2[4];
          bVar10 = true;
          psVar8 = psVar8 + 9;
          pcVar9 = (char *)((int)puVar2 + 0x12);
          do {
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            bVar10 = (char)*psVar8 == *pcVar9;
            psVar8 = (short *)((int)psVar8 + 1);
            pcVar9 = pcVar9 + 1;
          } while (bVar10);
          if (!bVar10) {
            return 1;
          }
          *param_3 = uVar1 | 0xc;
        }
      }
      return (byte)~(byte)*param_3 >> 3 & 1;
    }
    if (param_1[3] != 0) {
      return 1;
    }
    *param_3 = *param_3 | 0xe;
  }
  return 0;
}



/* === FUN_0040a8e6 @ 0040a8e6 === */

undefined4 FUN_0040a8e6(int param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}



/* === FUN_0040a8fa @ 0040a8fa === */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040a8fa(int param_1,uint *param_2)

{
  short *psVar1;
  int iVar2;
  float fVar3;
  
  if ((param_2 != (uint *)0x0) && (psVar1 = *(short **)(param_1 + 0xc), psVar1 != (short *)0x0)) {
    if (*psVar1 == -2) {
      *param_2 = *(uint *)(psVar1 + 0xc);
      param_2[1] = *(uint *)(psVar1 + 0xe);
      param_2[2] = *(uint *)(psVar1 + 0x10);
      param_2[3] = *(uint *)(psVar1 + 0x12);
      param_2[4] = (uint)(ushort)psVar1[1];
      param_2[5] = (uint)((ushort)psVar1[7] >> 3);
      param_2[6] = (uint)(ushort)psVar1[9];
      fVar3 = (float)*(int *)(psVar1 + 2);
      if (*(int *)(psVar1 + 2) < 0) {
        fVar3 = fVar3 + _DAT_00402168;
      }
      param_2[7] = (uint)fVar3;
      param_2[8] = *(uint *)(psVar1 + 10);
    }
    else {
      *param_2 = DAT_00402158;
      param_2[1] = _DAT_0040215c;
      param_2[2] = DAT_00402160;
      param_2[3] = DAT_00402164;
      *param_2 = (uint)**(ushort **)(param_1 + 0xc);
      param_2[4] = (uint)*(ushort *)(*(int *)(param_1 + 0xc) + 2);
      param_2[5] = (uint)(*(ushort *)(*(int *)(param_1 + 0xc) + 0xe) >> 3);
      param_2[6] = (uint)*(ushort *)(*(int *)(param_1 + 0xc) + 0xe);
      iVar2 = *(int *)(*(int *)(param_1 + 0xc) + 4);
      fVar3 = (float)iVar2;
      if (iVar2 < 0) {
        fVar3 = fVar3 + _DAT_00402168;
      }
      param_2[8] = 0;
      param_2[7] = (uint)fVar3;
    }
    if (*(float *)(param_1 + 0x10) != (float)_DAT_00402150) {
      param_2[7] = *(uint *)(param_1 + 0x10);
    }
    return 0;
  }
  return 0x80004003;
}



/* === FUN_0040a9d6 @ 0040a9d6 === */

short FUN_0040a9d6(short *param_1)

{
  short sVar1;
  int iVar2;
  short *psVar3;
  short *psVar4;
  bool bVar5;
  
  sVar1 = *param_1;
  if (sVar1 == -2) {
    iVar2 = 7;
    bVar5 = true;
    psVar3 = (short *)((int)&DAT_00402158 + 2);
    psVar4 = param_1 + 0xd;
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar5 = *psVar3 == *psVar4;
      psVar3 = psVar3 + 1;
      psVar4 = psVar4 + 1;
    } while (bVar5);
    if (bVar5) {
      sVar1 = param_1[0xc];
    }
    else {
      sVar1 = 0;
    }
  }
  return sVar1;
}



/* === FUN_0040aa0f @ 0040aa0f === */

undefined4 FUN_0040aa0f(int param_1)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if (((*(ushort *)(param_1 + 2) != 0) &&
      ((((uVar1 = *(ushort *)(param_1 + 0xe), uVar1 == 8 || (uVar1 == 0x10)) || (uVar1 == 0x18)) ||
       (uVar1 == 0x20)))) &&
     ((uint)*(ushort *)(param_1 + 0xc) == (uint)(uVar1 >> 3) * (uint)*(ushort *)(param_1 + 2))) {
    uVar2 = *(int *)(param_1 + 4) * (uint)*(ushort *)(param_1 + 0xc);
    uVar3 = 1;
    if ((uVar2 / 0x14 + uVar2 < *(uint *)(param_1 + 8)) ||
       (*(uint *)(param_1 + 8) < uVar2 - uVar2 / 0x14)) {
      uVar3 = 0;
    }
  }
  return uVar3;
}



/* === FUN_0040aa87 @ 0040aa87 === */

undefined4 FUN_0040aa87(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  if ((*(ushort *)(param_1 + 2) != 0) &&
     (((uVar1 = *(ushort *)(param_1 + 0xe), uVar1 == 0x20 || (uVar1 == 0x40)) &&
      (iVar2 = (uint)uVar1 * (uint)*(ushort *)(param_1 + 2),
      (uint)*(ushort *)(param_1 + 0xc) == (int)(iVar2 + (iVar2 >> 0x1f & 7U)) >> 3)))) {
    uVar3 = *(int *)(param_1 + 4) * (uint)*(ushort *)(param_1 + 0xc);
    uVar4 = 1;
    if ((uVar3 / 0x14 + uVar3 < *(uint *)(param_1 + 8)) ||
       (*(uint *)(param_1 + 8) < uVar3 - uVar3 / 0x14)) {
      uVar4 = 0;
    }
  }
  return uVar4;
}



/* === FUN_0040aaf9 @ 0040aaf9 === */

undefined4 FUN_0040aaf9(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((0x15 < *(ushort *)(param_1 + 0x10)) &&
     (*(ushort *)(param_1 + 0x12) <= *(ushort *)(param_1 + 0xe))) {
    uVar1 = 1;
  }
  return uVar1;
}



/* === FUN_0040ab1e @ 0040ab1e === */

int FUN_0040ab1e(short *param_1)

{
  short sVar1;
  int iVar2;
  
  sVar1 = FUN_0040a9d6(param_1);
  if (sVar1 == 1) {
    iVar2 = FUN_0040aa0f((int)param_1);
  }
  else {
    if (sVar1 != 3) {
      iVar2 = 1;
      goto LAB_0040ab4e;
    }
    iVar2 = FUN_0040aa87((int)param_1);
  }
  if (iVar2 == 0) {
    return 0;
  }
LAB_0040ab4e:
  if (*param_1 == -2) {
    iVar2 = FUN_0040aaf9((int)param_1);
  }
  return iVar2;
}



/* === FUN_0040ab65 @ 0040ab65 === */

void __fastcall FUN_0040ab65(undefined4 *param_1)

{
  param_1[4] = 0;
  *param_1 = &PTR_FUN_0040211c;
  param_1[1] = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  return;
}



/* === `scalar_deleting_destructor' @ 0040ab83 === */

/* Library Function - Single Match
    protected: virtual void * __thiscall CAudioMediaType::`scalar deleting destructor'(unsigned int)
   
   Libraries: Visual Studio 2012 Release, Visual Studio 2015 Release, Visual Studio 2017 Release,
   Visual Studio 2019 Release */

void * __thiscall CAudioMediaType::_scalar_deleting_destructor_(CAudioMediaType *this,uint param_1)

{
  ~CAudioMediaType(this);
  if ((param_1 & 1) != 0) {
    FUN_00402f2f(this);
  }
  return this;
}



/* === FUN_0040aba9 @ 0040aba9 === */

int __thiscall FUN_0040aba9(void *this,short *param_1,uint param_2)

{
  short sVar1;
  int iVar2;
  void *_Dst;
  int iVar3;
  int *piVar4;
  SIZE_T _Size;
  int *piVar5;
  int *piVar6;
  bool bVar7;
  uint local_8;
  
  local_8 = 0;
  if (param_1 == (short *)0x0) {
    return -0x7ff8ffa9;
  }
  iVar2 = FUN_0040ab1e(param_1);
  if (iVar2 == 0) {
    return -0x7ff8ffa9;
  }
  _Size = 0x12;
  iVar2 = FUN_0040a630((uint)(ushort)param_1[8],0x12,&local_8);
  if (iVar2 < 0) {
    return iVar2;
  }
  if (param_2 < local_8) {
    return -0x7ff8ffa9;
  }
  FUN_00402f2f(*(HLOCAL *)((int)this + 0xc));
  *(undefined4 *)((int)this + 0xc) = 0;
  if (*param_1 != 1) {
    _Size = (ushort)param_1[8] + 0x12;
  }
  _Dst = (void *)FUN_00402f11(_Size);
  *(void **)((int)this + 0xc) = _Dst;
  if (_Dst == (void *)0x0) {
    return -0x7ff8fff2;
  }
  memcpy(_Dst,param_1,_Size);
  if (*param_1 == 1) {
    *(undefined2 *)(*(int *)((int)this + 0xc) + 0x10) = 0;
  }
  sVar1 = **(short **)((int)this + 0xc);
  if (sVar1 == 0) {
    return iVar2;
  }
  if ((sVar1 != 1) && (sVar1 != 3)) {
    if (sVar1 != -2) {
LAB_0040ac9b:
      *(undefined4 *)((int)this + 8) = 1;
      return iVar2;
    }
    piVar6 = (int *)(*(short **)((int)this + 0xc) + 0xc);
    iVar3 = 4;
    bVar7 = true;
    piVar4 = &DAT_0040216c;
    piVar5 = piVar6;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = *piVar4 == *piVar5;
      piVar4 = piVar4 + 1;
      piVar5 = piVar5 + 1;
    } while (bVar7);
    if (!bVar7) {
      iVar3 = 4;
      bVar7 = true;
      piVar4 = &DAT_00401f28;
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar7 = *piVar4 == *piVar6;
        piVar4 = piVar4 + 1;
        piVar6 = piVar6 + 1;
      } while (bVar7);
      if (!bVar7) goto LAB_0040ac9b;
    }
  }
  *(undefined4 *)((int)this + 8) = 0;
  return iVar2;
}



/* === FUN_0040acb7 @ 0040acb7 === */

int FUN_0040acb7(short *param_1,uint param_2,undefined4 *param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int *this;
  
  if (param_3 == (undefined4 *)0x0) {
    iVar1 = -0x7ff8ffa9;
  }
  else {
    *param_3 = 0;
    puVar2 = (undefined4 *)FUN_00402f11(0x14);
    if (puVar2 == (undefined4 *)0x0) {
      this = (int *)0x0;
    }
    else {
      this = (int *)FUN_0040ab65(puVar2);
    }
    if (this == (int *)0x0) {
      iVar1 = -0x7ff8fff2;
    }
    else {
      if ((param_1 == (short *)0x0) || (iVar1 = FUN_0040aba9(this,param_1,param_2), -1 < iVar1)) {
        this[4] = param_4;
        iVar1 = (**(code **)*this)(this,&DAT_0040213c,param_3);
        if (-1 < iVar1) {
          return iVar1;
        }
      }
      (**(code **)(*this + 0x1c))(1);
    }
    *param_3 = 0;
  }
  return iVar1;
}



/* === FUN_0040ad3e @ 0040ad3e === */

void __fastcall FUN_0040ad3e(undefined4 param_1,undefined4 param_2,int *param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 extraout_EDX;
  int *piVar2;
  int *piVar3;
  bool bVar4;
  short local_30;
  short local_2e;
  undefined2 uStack_2c;
  undefined2 uStack_2a;
  int local_28;
  ushort local_24;
  short local_22;
  ushort local_20;
  undefined2 local_1e;
  int local_1c;
  int local_18;
  int iStack_14;
  int iStack_10;
  int iStack_c;
  uint local_8;
  
  local_8 = DAT_0040d060 ^ (uint)&stack0xfffffffc;
  if (param_3 == (int *)0x0) goto LAB_0040ae2c;
  local_2e = (short)param_3[4];
  local_28 = ftol2();
  uStack_2c = (undefined2)local_28;
  uStack_2a = (undefined2)((uint)local_28 >> 0x10);
  local_24 = (short)param_3[5] * local_2e;
  local_28 = (uint)local_24 * local_28;
  local_22 = (short)param_3[5] << 3;
  if (((uint)param_3[4] < 3) && (param_3[6] == param_3[5] << 3)) {
    iVar1 = 4;
    bVar4 = true;
    piVar2 = &DAT_0040216c;
    piVar3 = param_3;
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar4 = *piVar2 == *piVar3;
      piVar2 = piVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (bVar4);
    if (!bVar4) {
      iVar1 = 4;
      bVar4 = true;
      piVar2 = &DAT_00401f28;
      piVar3 = param_3;
      do {
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        bVar4 = *piVar2 == *piVar3;
        piVar2 = piVar2 + 1;
        piVar3 = piVar3 + 1;
      } while (bVar4);
      if (!bVar4) goto LAB_0040adec;
    }
    bVar4 = true;
    iVar1 = 4;
    piVar2 = &DAT_0040216c;
    piVar3 = param_3;
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar4 = *piVar2 == *piVar3;
      piVar2 = piVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (bVar4);
    local_20 = 0;
    local_30 = (ushort)!bVar4 * 2 + 1;
  }
  else {
LAB_0040adec:
    local_1e = (undefined2)param_3[6];
    local_1c = param_3[8];
    local_30 = -2;
    local_20 = 0x16;
    local_18 = *param_3;
    iStack_14 = param_3[1];
    iStack_10 = param_3[2];
    iStack_c = param_3[3];
  }
  FUN_0040acb7(&local_30,local_20 + 0x12,param_4,param_3[7]);
  param_2 = extraout_EDX;
LAB_0040ae2c:
  FUN_00409330(local_8 ^ (uint)&stack0xfffffffc,param_2);
  return;
}



/* === ftol2 @ 0040ae46 === */

void __cdecl ftol2(void)

{
                    /* WARNING: Could not recover jumptable at 0x0040ae46. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ftol2();
  return;
}



/* === FUN_0040c1de @ 0040c1de === */

undefined4 FUN_0040c1de(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(param_1 + 0x48c);
  if (uVar2 == 0) {
    param_2 = FUN_0040c298(param_1,param_2);
  }
  else {
    do {
      uVar2 = uVar2 - 1;
      puVar1 = (undefined4 *)FUN_00403145((void *)(param_1 + 0x490),uVar2);
      param_2 = (**(code **)(*(int *)*puVar1 + 0x10))((int *)*puVar1,param_2);
    } while (uVar2 != 0);
  }
  return param_2;
}



/* === FUN_0040c231 @ 0040c231 === */

undefined4 FUN_0040c231(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0x48c) == 0) {
    uVar1 = FUN_0040c298(param_1,param_2);
  }
  else {
    uVar3 = 0;
    if (*(int *)(param_1 + 0x48c) != 0) {
      do {
        puVar2 = (undefined4 *)FUN_00403145((void *)(param_1 + 0x490),uVar3);
        uVar1 = (**(code **)(*(int *)*puVar2 + 0x14))((int *)*puVar2,param_2);
        uVar3 = uVar3 + 1;
        param_2 = uVar1;
      } while (uVar3 < *(uint *)(param_1 + 0x48c));
    }
  }
  return uVar1;
}



/* === FUN_0040c286 @ 0040c286 === */

undefined4 __fastcall FUN_0040c286(int param_1)

{
  return *(undefined4 *)(param_1 + 0x2c);
}



/* === FUN_0040c28f @ 0040c28f === */

undefined4 __fastcall FUN_0040c28f(int param_1)

{
  return *(undefined4 *)(param_1 + 0x30);
}



/* === FUN_0040c298 @ 0040c298 === */

undefined4 FUN_0040c298(undefined4 param_1,undefined4 param_2)

{
  return param_2;
}



