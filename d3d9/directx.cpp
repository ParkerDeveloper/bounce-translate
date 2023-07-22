#include "directx.h"
#include "proxydirectx.h"
#include "d3drender.h"

CDirectX::CDirectX(IDirect3DDevice9 *dx) : QObject(nullptr)
{
	_dx = dx;
}

IDirect3DDevice9 *CDirectX::d3d9_device()
{
	return dynamic_cast<proxyIDirect3DDevice9*>(_dx)->getOriginalDevice();
}

proxyIDirect3DDevice9 *CDirectX::d3d9_this()
{
	return dynamic_cast<proxyIDirect3DDevice9*>(_dx);
}

HRESULT CDirectX::d3d9_GenerateShader(IDirect3DPixelShader9 **pShader, float alpha, float red, float green, float blue)
{
	return dynamic_cast<proxyIDirect3DDevice9*>(_dx)->GenerateShader(pShader, alpha, red, green, blue);
}

void CDirectX::d3d9_hook()
{
	_hook = true;
}

CD3DFont *CDirectX::d3d9_CreateFont(const char *szFontName, int fontHeight, DWORD dwCreateFlags)
{
	CD3DFont *pFont = new CD3DFont(szFontName, fontHeight, dwCreateFlags);
	dynamic_cast<proxyIDirect3DDevice9*>(_dx)->RegisterFont(pFont);
	return pFont;
}

CD3DRender *CDirectX::d3d9_CreateRender(int numVertices)
{
	CD3DRender *pRender = new CD3DRender(numVertices);
	dynamic_cast<proxyIDirect3DDevice9*>(_dx)->RegisterRender(pRender);
	return pRender;
}

SRTexture *CDirectX::d3d9_CreateTexture(int width, int height)
{
	SRTexture *pTexture = new SRTexture(width, height);
	dynamic_cast<proxyIDirect3DDevice9*>(_dx)->RegisterTexture(pTexture);
	return pTexture;
}

void CDirectX::d3d9_ReleaseFont(CD3DFont *pFont)
{
	dynamic_cast<proxyIDirect3DDevice9*>(_dx)->ReleaseFont(pFont);
}

void CDirectX::d3d9_ReleaseRender(CD3DRender *pRender)
{
	dynamic_cast<proxyIDirect3DDevice9*>(_dx)->ReleaseRender(pRender);
}

void CDirectX::d3d9_ReleaseTexture(SRTexture *pTexture)
{
	dynamic_cast<proxyIDirect3DDevice9*>(_dx)->ReleaseTexture(pTexture);
}

bool CDirectX::__d3d9_isHooked()
{
	bool ret = _hook;
	_hook = false;
	return ret;
}

HRESULT CDirectX::__d3d9_QueryInterface(const IID &riid, void **ppvObj)
{
	return QueryInterface(riid, ppvObj);
}

ULONG CDirectX::__d3d9_AddRef()
{
	return AddRef();
}

ULONG CDirectX::__d3d9_Release()
{
	return Release();
}

HRESULT CDirectX::__d3d9_TestCooperativeLevel()
{
	return TestCooperativeLevel();
}

UINT CDirectX::__d3d9_GetAvailableTextureMem()
{
	return GetAvailableTextureMem();
}

HRESULT CDirectX::__d3d9_EvictManagedResources()
{
	return EvictManagedResources();
}

HRESULT CDirectX::__d3d9_GetDirect3D(IDirect3D9 **ppD3D9)
{
	return GetDirect3D(ppD3D9);
}

HRESULT CDirectX::__d3d9_GetDeviceCaps(D3DCAPS9 *pCaps)
{
	return GetDeviceCaps(pCaps);
}

HRESULT CDirectX::__d3d9_GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE *pMode)
{
	return GetDisplayMode(iSwapChain, pMode);
}

HRESULT CDirectX::__d3d9_GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
	return GetCreationParameters(pParameters);
}

HRESULT CDirectX::__d3d9_SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 *pCursorBitmap)
{
	return SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void CDirectX::__d3d9_SetCursorPosition(int X, int Y, DWORD Flags)
{
	return SetCursorPosition(X, Y, Flags);
}

WINBOOL CDirectX::__d3d9_ShowCursor(WINBOOL bShow)
{
	return ShowCursor(bShow);
}

HRESULT CDirectX::__d3d9_CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9 **pSwapChain)
{
	return CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT CDirectX::__d3d9_GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9 **pSwapChain)
{
	return GetSwapChain(iSwapChain, pSwapChain);
}

UINT CDirectX::__d3d9_GetNumberOfSwapChains()
{
	return GetNumberOfSwapChains();
}

HRESULT CDirectX::__d3d9_Reset(D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	return Reset(pPresentationParameters);
}

HRESULT CDirectX::__d3d9_Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	return Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT CDirectX::__d3d9_GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9 **ppBackBuffer)
{
	return GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT CDirectX::__d3d9_GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS *pRasterStatus)
{
	return GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT CDirectX::__d3d9_SetDialogBoxMode(WINBOOL bEnableDialogs)
{
	return SetDialogBoxMode(bEnableDialogs);
}

void CDirectX::__d3d9_SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP *pRamp)
{
	return SetGammaRamp(iSwapChain, Flags, pRamp);
}

void CDirectX::__d3d9_GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP *pRamp)
{
	return GetGammaRamp(iSwapChain, pRamp);
}

HRESULT CDirectX::__d3d9_CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9 **ppTexture, HANDLE *pSharedHandle)
{
	return CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT CDirectX::__d3d9_CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 **ppVolumeTexture, HANDLE *pSharedHandle)
{
	return CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT CDirectX::__d3d9_CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9 **ppCubeTexture, HANDLE *pSharedHandle)
{
	return CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT CDirectX::__d3d9_CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle)
{
	return CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT CDirectX::__d3d9_CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle)
{
	return CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT CDirectX::__d3d9_CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, WINBOOL Lockable, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle)
{
	return CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT CDirectX::__d3d9_CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, WINBOOL Discard, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle)
{
	return CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT CDirectX::__d3d9_UpdateSurface(IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestinationSurface, const POINT *pDestPoint)
{
	return UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT CDirectX::__d3d9_UpdateTexture(IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture)
{
	return UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT CDirectX::__d3d9_GetRenderTargetData(IDirect3DSurface9 *pRenderTarget, IDirect3DSurface9 *pDestSurface)
{
	return GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT CDirectX::__d3d9_GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9 *pDestSurface)
{
	return GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT CDirectX::__d3d9_StretchRect(IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, const RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT CDirectX::__d3d9_ColorFill(IDirect3DSurface9 *pSurface, const RECT *pRect, D3DCOLOR color)
{
	return ColorFill(pSurface, pRect, color);
}

HRESULT CDirectX::__d3d9_CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle)
{
	return CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT CDirectX::__d3d9_SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget)
{
	return SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT CDirectX::__d3d9_GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9 **ppRenderTarget)
{
	return GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT CDirectX::__d3d9_SetDepthStencilSurface(IDirect3DSurface9 *pNewZStencil)
{
	return SetDepthStencilSurface(pNewZStencil);
}

HRESULT CDirectX::__d3d9_GetDepthStencilSurface(IDirect3DSurface9 **ppZStencilSurface)
{
	return GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT CDirectX::__d3d9_BeginScene()
{
	return BeginScene();
}

HRESULT CDirectX::__d3d9_EndScene()
{
	return EndScene();
}

HRESULT CDirectX::__d3d9_Clear(DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT CDirectX::__d3d9_SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
	return SetTransform(State, pMatrix);
}

HRESULT CDirectX::__d3d9_GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix)
{
	return GetTransform(State, pMatrix);
}

HRESULT CDirectX::__d3d9_MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
	return MultiplyTransform(State, pMatrix);
}

HRESULT CDirectX::__d3d9_SetViewport(const D3DVIEWPORT9 *pViewport)
{
	return SetViewport(pViewport);
}

HRESULT CDirectX::__d3d9_GetViewport(D3DVIEWPORT9 *pViewport)
{
	return GetViewport(pViewport);
}

HRESULT CDirectX::__d3d9_SetMaterial(const D3DMATERIAL9 *pMaterial)
{
	return SetMaterial(pMaterial);
}

HRESULT CDirectX::__d3d9_GetMaterial(D3DMATERIAL9 *pMaterial)
{
	return GetMaterial(pMaterial);
}

HRESULT CDirectX::__d3d9_SetLight(DWORD Index, const D3DLIGHT9 *pLight)
{
	return SetLight(Index, pLight);
}

HRESULT CDirectX::__d3d9_GetLight(DWORD Index, D3DLIGHT9 *pLight)
{
	return GetLight(Index, pLight);
}

HRESULT CDirectX::__d3d9_LightEnable(DWORD Index, WINBOOL Enable)
{
	return LightEnable(Index, Enable);
}

HRESULT CDirectX::__d3d9_GetLightEnable(DWORD Index, WINBOOL *pEnable)
{
	return GetLightEnable(Index, pEnable);
}

HRESULT CDirectX::__d3d9_SetClipPlane(DWORD Index, const float *pPlane)
{
	return SetClipPlane(Index, pPlane);
}

HRESULT CDirectX::__d3d9_GetClipPlane(DWORD Index, float *pPlane)
{
	return GetClipPlane(Index, pPlane);
}

HRESULT CDirectX::__d3d9_SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return SetRenderState(State, Value);
}

HRESULT CDirectX::__d3d9_GetRenderState(D3DRENDERSTATETYPE State, DWORD *pValue)
{
	return GetRenderState(State, pValue);
}

HRESULT CDirectX::__d3d9_CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9 **ppSB)
{
	return CreateStateBlock(Type, ppSB);
}

HRESULT CDirectX::__d3d9_BeginStateBlock()
{
	return BeginStateBlock();
}

HRESULT CDirectX::__d3d9_EndStateBlock(IDirect3DStateBlock9 **ppSB)
{
	return EndStateBlock(ppSB);
}

HRESULT CDirectX::__d3d9_SetClipStatus(const D3DCLIPSTATUS9 *pClipStatus)
{
	return SetClipStatus(pClipStatus);
}

HRESULT CDirectX::__d3d9_GetClipStatus(D3DCLIPSTATUS9 *pClipStatus)
{
	return GetClipStatus(pClipStatus);
}

HRESULT CDirectX::__d3d9_GetTexture(DWORD Stage, IDirect3DBaseTexture9 **ppTexture)
{
	return GetTexture(Stage, ppTexture);
}

HRESULT CDirectX::__d3d9_SetTexture(DWORD Stage, IDirect3DBaseTexture9 *pTexture)
{
	return SetTexture(Stage, pTexture);
}

HRESULT CDirectX::__d3d9_GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue)
{
	return GetTextureStageState(Stage, Type, pValue);
}

HRESULT CDirectX::__d3d9_SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return SetTextureStageState(Stage, Type, Value);
}

HRESULT CDirectX::__d3d9_GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD *pValue)
{
	return GetSamplerState(Sampler, Type, pValue);
}

HRESULT CDirectX::__d3d9_SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return SetSamplerState(Sampler, Type, Value);
}

HRESULT CDirectX::__d3d9_ValidateDevice(DWORD *pNumPasses)
{
	return ValidateDevice(pNumPasses);
}

HRESULT CDirectX::__d3d9_SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY *pEntries)
{
	return SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT CDirectX::__d3d9_GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY *pEntries)
{
	return GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT CDirectX::__d3d9_SetCurrentTexturePalette(UINT PaletteNumber)
{
	return SetCurrentTexturePalette(PaletteNumber);
}

HRESULT CDirectX::__d3d9_GetCurrentTexturePalette(UINT *PaletteNumber)
{
	return GetCurrentTexturePalette(PaletteNumber);
}

HRESULT CDirectX::__d3d9_SetScissorRect(const RECT *pRect)
{
	return SetScissorRect(pRect);
}

HRESULT CDirectX::__d3d9_GetScissorRect(RECT *pRect)
{
	return GetScissorRect(pRect);
}

HRESULT CDirectX::__d3d9_SetSoftwareVertexProcessing(WINBOOL bSoftware)
{
	return SetSoftwareVertexProcessing(bSoftware);
}

WINBOOL CDirectX::__d3d9_GetSoftwareVertexProcessing()
{
	return GetSoftwareVertexProcessing();
}

HRESULT CDirectX::__d3d9_SetNPatchMode(float nSegments)
{
	return SetNPatchMode(nSegments);
}

float CDirectX::__d3d9_GetNPatchMode()
{
	return GetNPatchMode();
}

HRESULT CDirectX::__d3d9_DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT CDirectX::__d3d9_DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT CDirectX::__d3d9_DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT CDirectX::__d3d9_DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void *pIndexData, D3DFORMAT IndexDataFormat, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT CDirectX::__d3d9_ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9 *pDestBuffer, IDirect3DVertexDeclaration9 *pVertexDecl, DWORD Flags)
{
	return ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT CDirectX::__d3d9_CreateVertexDeclaration(const D3DVERTEXELEMENT9 *pVertexElements, IDirect3DVertexDeclaration9 **ppDecl)
{
	return CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT CDirectX::__d3d9_SetVertexDeclaration(IDirect3DVertexDeclaration9 *pDecl)
{
	return SetVertexDeclaration(pDecl);
}

HRESULT CDirectX::__d3d9_GetVertexDeclaration(IDirect3DVertexDeclaration9 **ppDecl)
{
	return GetVertexDeclaration(ppDecl);
}

HRESULT CDirectX::__d3d9_SetFVF(DWORD FVF)
{
	return SetFVF(FVF);
}

HRESULT CDirectX::__d3d9_GetFVF(DWORD *pFVF)
{
	return GetFVF(pFVF);
}

HRESULT CDirectX::__d3d9_CreateVertexShader(const DWORD *pFunction, IDirect3DVertexShader9 **ppShader)
{
	return CreateVertexShader(pFunction, ppShader);
}

HRESULT CDirectX::__d3d9_SetVertexShader(IDirect3DVertexShader9 *pShader)
{
	return SetVertexShader(pShader);
}

HRESULT CDirectX::__d3d9_GetVertexShader(IDirect3DVertexShader9 **ppShader)
{
	return GetVertexShader(ppShader);
}

HRESULT CDirectX::__d3d9_SetVertexShaderConstantF(UINT StartRegister, const float *pConstantData, UINT Vector4fCount)
{
	return SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_GetVertexShaderConstantF(UINT StartRegister, float *pConstantData, UINT Vector4fCount)
{
	return GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_SetVertexShaderConstantI(UINT StartRegister, const int *pConstantData, UINT Vector4iCount)
{
	return SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT CDirectX::__d3d9_GetVertexShaderConstantI(UINT StartRegister, int *pConstantData, UINT Vector4fCount)
{
	return GetVertexShaderConstantI(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_SetVertexShaderConstantB(UINT StartRegister, const BOOL *pConstantData, UINT Vector4iCount)
{
	return SetVertexShaderConstantB(StartRegister, pConstantData, Vector4iCount);
}

HRESULT CDirectX::__d3d9_GetVertexShaderConstantB(UINT StartRegister, BOOL *pConstantData, UINT Vector4fCount)
{
	return GetVertexShaderConstantB(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT CDirectX::__d3d9_GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9 **ppStreamData, UINT *OffsetInBytes, UINT *pStride)
{
	return GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);
}

HRESULT CDirectX::__d3d9_SetStreamSourceFreq(UINT StreamNumber, UINT Divider)
{
	return SetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT CDirectX::__d3d9_GetStreamSourceFreq(UINT StreamNumber, UINT *Divider)
{
	return GetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT CDirectX::__d3d9_SetIndices(IDirect3DIndexBuffer9 *pIndexData)
{
	return SetIndices(pIndexData);
}

HRESULT CDirectX::__d3d9_GetIndices(IDirect3DIndexBuffer9 **ppIndexData)
{
	return GetIndices(ppIndexData);
}

HRESULT CDirectX::__d3d9_CreatePixelShader(const DWORD *pFunction, IDirect3DPixelShader9 **ppShader)
{
	return CreatePixelShader(pFunction, ppShader);
}

HRESULT CDirectX::__d3d9_SetPixelShader(IDirect3DPixelShader9 *pShader)
{
	return SetPixelShader(pShader);
}

HRESULT CDirectX::__d3d9_GetPixelShader(IDirect3DPixelShader9 **ppShader)
{
	return GetPixelShader(ppShader);
}

HRESULT CDirectX::__d3d9_SetPixelShaderConstantF(UINT StartRegister, const float *pConstantData, UINT Vector4fCount)
{
	return SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_GetPixelShaderConstantF(UINT StartRegister, float *pConstantData, UINT Vector4fCount)
{
	return GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_SetPixelShaderConstantI(UINT StartRegister, const int *pConstantData, UINT Vector4fCount)
{
	return SetPixelShaderConstantI(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_GetPixelShaderConstantI(UINT StartRegister, int *pConstantData, UINT Vector4fCount)
{
	return GetPixelShaderConstantI(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_SetPixelShaderConstantB(UINT StartRegister, const BOOL *pConstantData, UINT Vector4fCount)
{
	return SetPixelShaderConstantB(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_GetPixelShaderConstantB(UINT StartRegister, BOOL *pConstantData, UINT Vector4fCount)
{
	return GetPixelShaderConstantB(StartRegister, pConstantData, Vector4fCount);
}

HRESULT CDirectX::__d3d9_DrawRectPatch(UINT Handle, const float *pNumSegs, const D3DRECTPATCH_INFO *pRectPatchInfo)
{
	return DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT CDirectX::__d3d9_DrawTriPatch(UINT Handle, const float *pNumSegs, const D3DTRIPATCH_INFO *pTriPatchInfo)
{
	return DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT CDirectX::__d3d9_DeletePatch(UINT Handle)
{
	return DeletePatch(Handle);
}

HRESULT CDirectX::__d3d9_CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9 **ppQuery)
{
	return CreateQuery(Type, ppQuery);
}
