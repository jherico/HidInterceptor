#include <Windows.h>
#include <pshpack4.h>
#include <iostream>
#include <fstream>

#define HIDP_STATUS_SUCCESS (0x11 << 16)
struct HIDP_PREPARSED_DATA;

struct HIDD_ATTRIBUTES
{
  ULONG   Size; // = sizeof (struct _HIDD_ATTRIBUTES)
  USHORT  VendorID;
  USHORT  ProductID;
  USHORT  VersionNumber;
};

struct HIDP_CAPS
{
  USHORT   Usage;
  USHORT   UsagePage;
  USHORT   InputReportByteLength;
  USHORT   OutputReportByteLength;
  USHORT   FeatureReportByteLength;
  USHORT   Reserved[17];

  USHORT   NumberLinkCollectionNodes;
  USHORT   NumberInputButtonCaps;
  USHORT   NumberInputValueCaps;
  USHORT   NumberInputDataIndices;
  USHORT   NumberOutputButtonCaps;
  USHORT   NumberOutputValueCaps;
  USHORT   NumberOutputDataIndices;
  USHORT   NumberFeatureButtonCaps;
  USHORT   NumberFeatureValueCaps;
  USHORT   NumberFeatureDataIndices;
};
// Macros to declare and resolve needed functions from library.
#define OVR_DECLARE_HIDFUNC(func, rettype, args)   \
typedef rettype (__stdcall *PFn_##func) args;  \
PFn_##func      Real_##func;
#define OVR_RESOLVE_HIDFUNC(func) \
Real_##func = (PFn_##func)::GetProcAddress(hHidLib, #func)

OVR_DECLARE_HIDFUNC(HidD_GetHidGuid, void, (GUID *hidGuid));
OVR_DECLARE_HIDFUNC(HidD_SetNumInputBuffers, BOOLEAN, (HANDLE hidDev, ULONG numberBuffers));
OVR_DECLARE_HIDFUNC(HidD_GetFeature, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_SetFeature, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetAttributes, BOOLEAN, (HANDLE hidDev, HIDD_ATTRIBUTES *attributes));
OVR_DECLARE_HIDFUNC(HidD_GetManufacturerString, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetProductString, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetSerialNumberString, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetPreparsedData, BOOLEAN, (HANDLE hidDev, HIDP_PREPARSED_DATA **preparsedData));
OVR_DECLARE_HIDFUNC(HidD_FreePreparsedData, BOOLEAN, (HIDP_PREPARSED_DATA *preparsedData));
OVR_DECLARE_HIDFUNC(HidP_GetCaps, NTSTATUS, (HIDP_PREPARSED_DATA *preparsedData, HIDP_CAPS* caps));

void HidD_GetHidGuid(GUID *hidGuid) {
  Real_HidD_GetHidGuid(hidGuid);
}

BOOLEAN HidD_SetNumInputBuffers(HANDLE hidDev, ULONG numberBuffers) {
  return Real_HidD_SetNumInputBuffers(hidDev, numberBuffers);
}

BOOLEAN HidD_GetFeature(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  return Real_HidD_GetFeature(hidDev, buffer, bufferLength);
}

BOOLEAN HidD_SetFeature(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  return Real_HidD_SetFeature(hidDev, buffer, bufferLength);
}

BOOLEAN HidD_GetAttributes(HANDLE hidDev, HIDD_ATTRIBUTES *attributes) {
  return Real_HidD_GetAttributes(hidDev, attributes);
}

BOOLEAN HidD_GetManufacturerString(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  return Real_HidD_GetManufacturerString(hidDev, buffer, bufferLength);
}

BOOLEAN HidD_GetProductString(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  return Real_HidD_GetProductString(hidDev, buffer, bufferLength);
}

BOOLEAN HidD_GetSerialNumberString(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  return Real_HidD_GetSerialNumberString(hidDev, buffer, bufferLength);
}

BOOLEAN HidD_GetPreparsedData(HANDLE hidDev, HIDP_PREPARSED_DATA **preparsedData) {
  return Real_HidD_GetPreparsedData(hidDev, preparsedData);
}

BOOLEAN HidD_FreePreparsedData(HIDP_PREPARSED_DATA *preparsedData) {
  return Real_HidD_FreePreparsedData(preparsedData);
}

NTSTATUS HidP_GetCaps(HIDP_PREPARSED_DATA *preparsedData, HIDP_CAPS* caps) {
  return Real_HidP_GetCaps(preparsedData, caps);
}

HMODULE hHidLib;
GUID    HidGuid;

using namespace std;
BOOL WINAPI DllMain(
  _In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved
  ) {
  hHidLib = ::LoadLibraryA("C:\\Windows\\System32\\hid.dll");

  {
    ofstream of("f:\\test.txt");
    of << "Loading dll" << endl;
    of.flush();
    of.close();
  }
  OVR_RESOLVE_HIDFUNC(HidD_GetHidGuid);
  OVR_RESOLVE_HIDFUNC(HidD_SetNumInputBuffers);
  OVR_RESOLVE_HIDFUNC(HidD_GetFeature);
  OVR_RESOLVE_HIDFUNC(HidD_SetFeature);
  OVR_RESOLVE_HIDFUNC(HidD_GetAttributes);
  OVR_RESOLVE_HIDFUNC(HidD_GetManufacturerString);
  OVR_RESOLVE_HIDFUNC(HidD_GetProductString);
  OVR_RESOLVE_HIDFUNC(HidD_GetSerialNumberString);
  OVR_RESOLVE_HIDFUNC(HidD_GetPreparsedData);
  OVR_RESOLVE_HIDFUNC(HidD_FreePreparsedData);
  OVR_RESOLVE_HIDFUNC(HidP_GetCaps);
}
