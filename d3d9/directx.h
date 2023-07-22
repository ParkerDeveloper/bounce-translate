#ifndef DIRECTX_H
#define DIRECTX_H

#include <QObject>
#include <d3d9.h>
#include <d3dx9.h>
#include <wingdi.h>
#include <d3dx9core.h>

class CDirectX : public QObject
{
	friend class proxyIDirect3DDevice9;
	Q_OBJECT
public:
	explicit CDirectX(IDirect3DDevice9* dx);

	IDirect3DDevice9 *d3d9_device();
	class proxyIDirect3DDevice9 *d3d9_this();
	HRESULT d3d9_GenerateShader(IDirect3DPixelShader9 **pShader, float alpha, float red, float green, float blue);
	void d3d9_hook();

	class CD3DFont* d3d9_CreateFont(const char *szFontName, int fontHeight, DWORD dwCreateFlags = 4);
	class CD3DRender* d3d9_CreateRender(int numVertices = 128);
	class SRTexture* d3d9_CreateTexture(int width, int height);

	void d3d9_ReleaseFont(class CD3DFont* pFont);
	void d3d9_ReleaseRender(class CD3DRender* pRender);
	void d3d9_ReleaseTexture(class SRTexture* pTexture);

protected:
	bool __d3d9_isHooked();
	HRESULT __stdcall	__d3d9_QueryInterface ( REFIID riid, void **ppvObj );
	ULONG __stdcall		__d3d9_AddRef ( void );
	ULONG __stdcall		__d3d9_Release ( void );
	HRESULT __stdcall	__d3d9_TestCooperativeLevel ( void );
	UINT __stdcall		__d3d9_GetAvailableTextureMem ( void );
	HRESULT __stdcall	__d3d9_EvictManagedResources ( void );
	HRESULT __stdcall	__d3d9_GetDirect3D ( IDirect3D9 **ppD3D9 );
	HRESULT __stdcall	__d3d9_GetDeviceCaps ( D3DCAPS9 *pCaps );
	HRESULT __stdcall	__d3d9_GetDisplayMode ( UINT iSwapChain, D3DDISPLAYMODE *pMode );
	HRESULT __stdcall	__d3d9_GetCreationParameters ( D3DDEVICE_CREATION_PARAMETERS *pParameters );
	HRESULT __stdcall	__d3d9_SetCursorProperties ( UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 *pCursorBitmap );
	void __stdcall		__d3d9_SetCursorPosition ( int X, int Y, DWORD Flags );
	BOOL __stdcall		__d3d9_ShowCursor ( BOOL bShow );
	HRESULT __stdcall	__d3d9_CreateAdditionalSwapChain ( D3DPRESENT_PARAMETERS *pPresentationParameters,
														   IDirect3DSwapChain9 **pSwapChain );
	HRESULT __stdcall	__d3d9_GetSwapChain ( UINT iSwapChain, IDirect3DSwapChain9 **pSwapChain );
	UINT __stdcall		__d3d9_GetNumberOfSwapChains ( void );
	HRESULT __stdcall	__d3d9_Reset ( D3DPRESENT_PARAMETERS *pPresentationParameters );
	HRESULT __stdcall	__d3d9_Present ( CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride,
										 CONST RGNDATA *pDirtyRegion );
	HRESULT __stdcall	__d3d9_GetBackBuffer ( UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type,
											   IDirect3DSurface9 **ppBackBuffer );
	HRESULT __stdcall	__d3d9_GetRasterStatus ( UINT iSwapChain, D3DRASTER_STATUS *pRasterStatus );
	HRESULT __stdcall	__d3d9_SetDialogBoxMode ( BOOL bEnableDialogs );
	void __stdcall		__d3d9_SetGammaRamp ( UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP *pRamp );
	void __stdcall		__d3d9_GetGammaRamp ( UINT iSwapChain, D3DGAMMARAMP *pRamp );
	HRESULT __stdcall	__d3d9_CreateTexture ( UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format,
											   D3DPOOL Pool, IDirect3DTexture9 **ppTexture, HANDLE *pSharedHandle );
	HRESULT __stdcall	__d3d9_CreateVolumeTexture ( UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage,
													 D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 **ppVolumeTexture,
													 HANDLE *pSharedHandle );
	HRESULT __stdcall	__d3d9_CreateCubeTexture ( UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
												   IDirect3DCubeTexture9 **ppCubeTexture, HANDLE *pSharedHandle );
	HRESULT __stdcall	__d3d9_CreateVertexBuffer ( UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool,
													IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle );
	HRESULT __stdcall	__d3d9_CreateIndexBuffer ( UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
												   IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle );
	HRESULT __stdcall	__d3d9_CreateRenderTarget ( UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample,
													DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9 **ppSurface,
													HANDLE *pSharedHandle );
	HRESULT __stdcall	__d3d9_CreateDepthStencilSurface ( UINT Width, UINT Height, D3DFORMAT Format,
														   D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality,
														   BOOL Discard, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle );
	HRESULT __stdcall	__d3d9_UpdateSurface ( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect,
											   IDirect3DSurface9 *pDestinationSurface, CONST POINT *pDestPoint );
	HRESULT __stdcall	__d3d9_UpdateTexture ( IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture );
	HRESULT __stdcall	__d3d9_GetRenderTargetData ( IDirect3DSurface9 *pRenderTarget, IDirect3DSurface9 *pDestSurface );
	HRESULT __stdcall	__d3d9_GetFrontBufferData ( UINT iSwapChain, IDirect3DSurface9 *pDestSurface );
	HRESULT __stdcall	__d3d9_StretchRect ( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect,
											 IDirect3DSurface9 *pDestSurface, CONST RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter );
	HRESULT __stdcall	__d3d9_ColorFill ( IDirect3DSurface9 *pSurface, CONST RECT *pRect, D3DCOLOR color );
	HRESULT __stdcall	__d3d9_CreateOffscreenPlainSurface ( UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool,
															 IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle );
	HRESULT __stdcall	__d3d9_SetRenderTarget ( DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget );
	HRESULT __stdcall	__d3d9_GetRenderTarget ( DWORD RenderTargetIndex, IDirect3DSurface9 **ppRenderTarget );
	HRESULT __stdcall	__d3d9_SetDepthStencilSurface ( IDirect3DSurface9 *pNewZStencil );
	HRESULT __stdcall	__d3d9_GetDepthStencilSurface ( IDirect3DSurface9 **ppZStencilSurface );
	HRESULT __stdcall	__d3d9_BeginScene ( void );
	HRESULT __stdcall	__d3d9_EndScene ( void );
	HRESULT __stdcall	__d3d9_Clear ( DWORD Count, CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil );
	HRESULT __stdcall	__d3d9_SetTransform ( D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix );
	HRESULT __stdcall	__d3d9_GetTransform ( D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix );
	HRESULT __stdcall	__d3d9_MultiplyTransform ( D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix );
	HRESULT __stdcall	__d3d9_SetViewport ( CONST D3DVIEWPORT9 *pViewport );
	HRESULT __stdcall	__d3d9_GetViewport ( D3DVIEWPORT9 *pViewport );
	HRESULT __stdcall	__d3d9_SetMaterial ( CONST D3DMATERIAL9 *pMaterial );
	HRESULT __stdcall	__d3d9_GetMaterial ( D3DMATERIAL9 *pMaterial );
	HRESULT __stdcall	__d3d9_SetLight ( DWORD Index, CONST D3DLIGHT9 *pLight );
	HRESULT __stdcall	__d3d9_GetLight ( DWORD Index, D3DLIGHT9 *pLight );
	HRESULT __stdcall	__d3d9_LightEnable ( DWORD Index, BOOL Enable );
	HRESULT __stdcall	__d3d9_GetLightEnable ( DWORD Index, BOOL *pEnable );
	HRESULT __stdcall	__d3d9_SetClipPlane ( DWORD Index, CONST float *pPlane );
	HRESULT __stdcall	__d3d9_GetClipPlane ( DWORD Index, float *pPlane );
	HRESULT __stdcall	__d3d9_SetRenderState ( D3DRENDERSTATETYPE State, DWORD Value );
	HRESULT __stdcall	__d3d9_GetRenderState ( D3DRENDERSTATETYPE State, DWORD *pValue );
	HRESULT __stdcall	__d3d9_CreateStateBlock ( D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9 **ppSB );
	HRESULT __stdcall	__d3d9_BeginStateBlock ( void );
	HRESULT __stdcall	__d3d9_EndStateBlock ( IDirect3DStateBlock9 **ppSB );
	HRESULT __stdcall	__d3d9_SetClipStatus ( CONST D3DCLIPSTATUS9 *pClipStatus );
	HRESULT __stdcall	__d3d9_GetClipStatus ( D3DCLIPSTATUS9 *pClipStatus );
	HRESULT __stdcall	__d3d9_GetTexture ( DWORD Stage, IDirect3DBaseTexture9 **ppTexture );
	HRESULT __stdcall	__d3d9_SetTexture ( DWORD Stage, IDirect3DBaseTexture9 *pTexture );
	HRESULT __stdcall	__d3d9_GetTextureStageState ( DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue );
	HRESULT __stdcall	__d3d9_SetTextureStageState ( DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value );
	HRESULT __stdcall	__d3d9_GetSamplerState ( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD *pValue );
	HRESULT __stdcall	__d3d9_SetSamplerState ( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value );
	HRESULT __stdcall	__d3d9_ValidateDevice ( DWORD *pNumPasses );
	HRESULT __stdcall	__d3d9_SetPaletteEntries ( UINT PaletteNumber, CONST PALETTEENTRY *pEntries );
	HRESULT __stdcall	__d3d9_GetPaletteEntries ( UINT PaletteNumber, PALETTEENTRY *pEntries );
	HRESULT __stdcall	__d3d9_SetCurrentTexturePalette ( UINT PaletteNumber );
	HRESULT __stdcall	__d3d9_GetCurrentTexturePalette ( UINT *PaletteNumber );
	HRESULT __stdcall	__d3d9_SetScissorRect ( CONST RECT *pRect );
	HRESULT __stdcall	__d3d9_GetScissorRect ( RECT *pRect );
	HRESULT __stdcall	__d3d9_SetSoftwareVertexProcessing ( BOOL bSoftware );
	BOOL __stdcall		__d3d9_GetSoftwareVertexProcessing ( void );
	HRESULT __stdcall	__d3d9_SetNPatchMode ( float nSegments );
	float __stdcall		__d3d9_GetNPatchMode ( void );
	HRESULT __stdcall	__d3d9_DrawPrimitive ( D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount );
	HRESULT __stdcall	__d3d9_DrawIndexedPrimitive ( D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex,
													  UINT NumVertices, UINT startIndex, UINT primCount );
	HRESULT __stdcall	__d3d9_DrawPrimitiveUP ( D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount,
												 CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride );
	HRESULT __stdcall	__d3d9_DrawIndexedPrimitiveUP ( D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices,
														UINT PrimitiveCount, CONST void *pIndexData, D3DFORMAT IndexDataFormat,
														CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride );
	HRESULT __stdcall	__d3d9_ProcessVertices ( UINT SrcStartIndex, UINT DestIndex, UINT VertexCount,
												 IDirect3DVertexBuffer9 *pDestBuffer, IDirect3DVertexDeclaration9 *pVertexDecl,
												 DWORD Flags );
	HRESULT __stdcall	__d3d9_CreateVertexDeclaration ( CONST D3DVERTEXELEMENT9 *pVertexElements,
														 IDirect3DVertexDeclaration9 **ppDecl );
	HRESULT __stdcall	__d3d9_SetVertexDeclaration ( IDirect3DVertexDeclaration9 *pDecl );
	HRESULT __stdcall	__d3d9_GetVertexDeclaration ( IDirect3DVertexDeclaration9 **ppDecl );
	HRESULT __stdcall	__d3d9_SetFVF ( DWORD FVF );
	HRESULT __stdcall	__d3d9_GetFVF ( DWORD *pFVF );
	HRESULT __stdcall	__d3d9_CreateVertexShader ( CONST DWORD *pFunction, IDirect3DVertexShader9 **ppShader );
	HRESULT __stdcall	__d3d9_SetVertexShader ( IDirect3DVertexShader9 *pShader );
	HRESULT __stdcall	__d3d9_GetVertexShader ( IDirect3DVertexShader9 **ppShader );
	HRESULT __stdcall	__d3d9_SetVertexShaderConstantF ( UINT StartRegister, CONST float *pConstantData, UINT Vector4fCount );
	HRESULT __stdcall	__d3d9_GetVertexShaderConstantF ( UINT StartRegister, float *pConstantData, UINT Vector4fCount );
	HRESULT __stdcall	__d3d9_SetVertexShaderConstantI ( UINT StartRegister, CONST int *pConstantData, UINT Vector4iCount );
	HRESULT __stdcall	__d3d9_GetVertexShaderConstantI ( UINT StartRegister, int *pConstantData, UINT Vector4iCount );
	HRESULT __stdcall	__d3d9_SetVertexShaderConstantB ( UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount );
	HRESULT __stdcall	__d3d9_GetVertexShaderConstantB ( UINT StartRegister, BOOL *pConstantData, UINT BoolCount );
	HRESULT __stdcall	__d3d9_SetStreamSource ( UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes,
												 UINT Stride );
	HRESULT __stdcall	__d3d9_GetStreamSource ( UINT StreamNumber, IDirect3DVertexBuffer9 **ppStreamData, UINT *OffsetInBytes,
												 UINT *pStride );
	HRESULT __stdcall	__d3d9_SetStreamSourceFreq ( UINT StreamNumber, UINT Divider );
	HRESULT __stdcall	__d3d9_GetStreamSourceFreq ( UINT StreamNumber, UINT *Divider );
	HRESULT __stdcall	__d3d9_SetIndices ( IDirect3DIndexBuffer9 *pIndexData );
	HRESULT __stdcall	__d3d9_GetIndices ( IDirect3DIndexBuffer9 **ppIndexData );
	HRESULT __stdcall	__d3d9_CreatePixelShader ( CONST DWORD *pFunction, IDirect3DPixelShader9 **ppShader );
	HRESULT __stdcall	__d3d9_SetPixelShader ( IDirect3DPixelShader9 *pShader );
	HRESULT __stdcall	__d3d9_GetPixelShader ( IDirect3DPixelShader9 **ppShader );
	HRESULT __stdcall	__d3d9_SetPixelShaderConstantF ( UINT StartRegister, CONST float *pConstantData, UINT Vector4fCount );
	HRESULT __stdcall	__d3d9_GetPixelShaderConstantF ( UINT StartRegister, float *pConstantData, UINT Vector4fCount );
	HRESULT __stdcall	__d3d9_SetPixelShaderConstantI ( UINT StartRegister, CONST int *pConstantData, UINT Vector4iCount );
	HRESULT __stdcall	__d3d9_GetPixelShaderConstantI ( UINT StartRegister, int *pConstantData, UINT Vector4iCount );
	HRESULT __stdcall	__d3d9_SetPixelShaderConstantB ( UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount );
	HRESULT __stdcall	__d3d9_GetPixelShaderConstantB ( UINT StartRegister, BOOL *pConstantData, UINT BoolCount );
	HRESULT __stdcall	__d3d9_DrawRectPatch ( UINT Handle, CONST float *pNumSegs, CONST D3DRECTPATCH_INFO *pRectPatchInfo );
	HRESULT __stdcall	__d3d9_DrawTriPatch ( UINT Handle, CONST float *pNumSegs, CONST D3DTRIPATCH_INFO *pTriPatchInfo );
	HRESULT __stdcall	__d3d9_DeletePatch ( UINT Handle );
	HRESULT __stdcall	__d3d9_CreateQuery ( D3DQUERYTYPE Type, IDirect3DQuery9 **ppQuery );

signals:
	HRESULT QueryInterface ( REFIID riid, void **ppvObj );
	ULONG 	AddRef ( void );
	ULONG 	Release ( void );
	HRESULT TestCooperativeLevel ( void );
	UINT 	GetAvailableTextureMem ( void );
	HRESULT EvictManagedResources ( void );
	HRESULT GetDirect3D ( IDirect3D9 **ppD3D9 );
	HRESULT GetDeviceCaps ( D3DCAPS9 *pCaps );
	HRESULT GetDisplayMode ( UINT iSwapChain, D3DDISPLAYMODE *pMode );
	HRESULT GetCreationParameters ( D3DDEVICE_CREATION_PARAMETERS *pParameters );
	HRESULT SetCursorProperties ( UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 *pCursorBitmap );
	void 	SetCursorPosition ( int X, int Y, DWORD Flags );
	BOOL 	ShowCursor ( BOOL bShow );
	HRESULT CreateAdditionalSwapChain ( D3DPRESENT_PARAMETERS *pPresentationParameters,
										IDirect3DSwapChain9 **pSwapChain );
	HRESULT GetSwapChain ( UINT iSwapChain, IDirect3DSwapChain9 **pSwapChain );
	UINT    GetNumberOfSwapChains ( void );
	HRESULT Reset ( D3DPRESENT_PARAMETERS *pPresentationParameters );
	HRESULT Present ( CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride,
					  CONST RGNDATA *pDirtyRegion );
	HRESULT GetBackBuffer ( UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type,
							IDirect3DSurface9 **ppBackBuffer );
	HRESULT GetRasterStatus ( UINT iSwapChain, D3DRASTER_STATUS *pRasterStatus );
	HRESULT SetDialogBoxMode ( BOOL bEnableDialogs );
	void 	SetGammaRamp ( UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP *pRamp );
	void 	GetGammaRamp ( UINT iSwapChain, D3DGAMMARAMP *pRamp );
	HRESULT CreateTexture ( UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format,
							D3DPOOL Pool, IDirect3DTexture9 **ppTexture, HANDLE *pSharedHandle );
	HRESULT CreateVolumeTexture ( UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage,
								  D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 **ppVolumeTexture,
								  HANDLE *pSharedHandle );
	HRESULT CreateCubeTexture ( UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
								IDirect3DCubeTexture9 **ppCubeTexture, HANDLE *pSharedHandle );
	HRESULT CreateVertexBuffer ( UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool,
								 IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle );
	HRESULT CreateIndexBuffer ( UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
								IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle );
	HRESULT CreateRenderTarget ( UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample,
								 DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9 **ppSurface,
								 HANDLE *pSharedHandle );
	HRESULT CreateDepthStencilSurface ( UINT Width, UINT Height, D3DFORMAT Format,
										D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality,
										BOOL Discard, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle );
	HRESULT UpdateSurface ( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect,
							IDirect3DSurface9 *pDestinationSurface, CONST POINT *pDestPoint );
	HRESULT UpdateTexture ( IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture );
	HRESULT GetRenderTargetData ( IDirect3DSurface9 *pRenderTarget, IDirect3DSurface9 *pDestSurface );
	HRESULT GetFrontBufferData ( UINT iSwapChain, IDirect3DSurface9 *pDestSurface );
	HRESULT StretchRect ( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect,
						  IDirect3DSurface9 *pDestSurface, CONST RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter );
	HRESULT ColorFill ( IDirect3DSurface9 *pSurface, CONST RECT *pRect, D3DCOLOR color );
	HRESULT CreateOffscreenPlainSurface ( UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool,
										  IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle );
	HRESULT SetRenderTarget ( DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget );
	HRESULT GetRenderTarget ( DWORD RenderTargetIndex, IDirect3DSurface9 **ppRenderTarget );
	HRESULT SetDepthStencilSurface ( IDirect3DSurface9 *pNewZStencil );
	HRESULT GetDepthStencilSurface ( IDirect3DSurface9 **ppZStencilSurface );
	HRESULT BeginScene ( void );
	HRESULT EndScene ( void );
	HRESULT Clear ( DWORD Count, CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil );
	HRESULT SetTransform ( D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix );
	HRESULT GetTransform ( D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix );
	HRESULT MultiplyTransform ( D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix );
	HRESULT SetViewport ( CONST D3DVIEWPORT9 *pViewport );
	HRESULT GetViewport ( D3DVIEWPORT9 *pViewport );
	HRESULT SetMaterial ( CONST D3DMATERIAL9 *pMaterial );
	HRESULT GetMaterial ( D3DMATERIAL9 *pMaterial );
	HRESULT SetLight ( DWORD Index, CONST D3DLIGHT9 *pLight );
	HRESULT GetLight ( DWORD Index, D3DLIGHT9 *pLight );
	HRESULT LightEnable ( DWORD Index, BOOL Enable );
	HRESULT GetLightEnable ( DWORD Index, BOOL *pEnable );
	HRESULT SetClipPlane ( DWORD Index, CONST float *pPlane );
	HRESULT GetClipPlane ( DWORD Index, float *pPlane );
	HRESULT SetRenderState ( D3DRENDERSTATETYPE State, DWORD Value );
	HRESULT GetRenderState ( D3DRENDERSTATETYPE State, DWORD *pValue );
	HRESULT CreateStateBlock ( D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9 **ppSB );
	HRESULT BeginStateBlock ( void );
	HRESULT EndStateBlock ( IDirect3DStateBlock9 **ppSB );
	HRESULT SetClipStatus ( CONST D3DCLIPSTATUS9 *pClipStatus );
	HRESULT GetClipStatus ( D3DCLIPSTATUS9 *pClipStatus );
	HRESULT GetTexture ( DWORD Stage, IDirect3DBaseTexture9 **ppTexture );
	HRESULT SetTexture ( DWORD Stage, IDirect3DBaseTexture9 *pTexture );
	HRESULT GetTextureStageState ( DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue );
	HRESULT SetTextureStageState ( DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value );
	HRESULT GetSamplerState ( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD *pValue );
	HRESULT SetSamplerState ( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value );
	HRESULT ValidateDevice ( DWORD *pNumPasses );
	HRESULT SetPaletteEntries ( UINT PaletteNumber, CONST PALETTEENTRY *pEntries );
	HRESULT GetPaletteEntries ( UINT PaletteNumber, PALETTEENTRY *pEntries );
	HRESULT SetCurrentTexturePalette ( UINT PaletteNumber );
	HRESULT GetCurrentTexturePalette ( UINT *PaletteNumber );
	HRESULT SetScissorRect ( CONST RECT *pRect );
	HRESULT GetScissorRect ( RECT *pRect );
	HRESULT SetSoftwareVertexProcessing ( BOOL bSoftware );
	BOOL 	GetSoftwareVertexProcessing ( void );
	HRESULT SetNPatchMode ( float nSegments );
	float 	GetNPatchMode ( void );
	HRESULT DrawPrimitive ( D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount );
	HRESULT DrawIndexedPrimitive ( D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex,
								   UINT NumVertices, UINT startIndex, UINT primCount );
	HRESULT DrawPrimitiveUP ( D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount,
							  CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride );
	HRESULT DrawIndexedPrimitiveUP ( D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices,
									 UINT PrimitiveCount, CONST void *pIndexData, D3DFORMAT IndexDataFormat,
									 CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride );
	HRESULT ProcessVertices ( UINT SrcStartIndex, UINT DestIndex, UINT VertexCount,
							  IDirect3DVertexBuffer9 *pDestBuffer, IDirect3DVertexDeclaration9 *pVertexDecl,
							  DWORD Flags );
	HRESULT CreateVertexDeclaration ( CONST D3DVERTEXELEMENT9 *pVertexElements,
									  IDirect3DVertexDeclaration9 **ppDecl );
	HRESULT SetVertexDeclaration ( IDirect3DVertexDeclaration9 *pDecl );
	HRESULT GetVertexDeclaration ( IDirect3DVertexDeclaration9 **ppDecl );
	HRESULT SetFVF ( DWORD FVF );
	HRESULT GetFVF ( DWORD *pFVF );
	HRESULT CreateVertexShader ( CONST DWORD *pFunction, IDirect3DVertexShader9 **ppShader );
	HRESULT SetVertexShader ( IDirect3DVertexShader9 *pShader );
	HRESULT GetVertexShader ( IDirect3DVertexShader9 **ppShader );
	HRESULT SetVertexShaderConstantF ( UINT StartRegister, CONST float *pConstantData, UINT Vector4fCount );
	HRESULT GetVertexShaderConstantF ( UINT StartRegister, float *pConstantData, UINT Vector4fCount );
	HRESULT SetVertexShaderConstantI ( UINT StartRegister, CONST int *pConstantData, UINT Vector4iCount );
	HRESULT GetVertexShaderConstantI ( UINT StartRegister, int *pConstantData, UINT Vector4iCount );
	HRESULT SetVertexShaderConstantB ( UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount );
	HRESULT GetVertexShaderConstantB ( UINT StartRegister, BOOL *pConstantData, UINT BoolCount );
	HRESULT SetStreamSource ( UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes,
							  UINT Stride );
	HRESULT GetStreamSource ( UINT StreamNumber, IDirect3DVertexBuffer9 **ppStreamData, UINT *OffsetInBytes,
							  UINT *pStride );
	HRESULT SetStreamSourceFreq ( UINT StreamNumber, UINT Divider );
	HRESULT GetStreamSourceFreq ( UINT StreamNumber, UINT *Divider );
	HRESULT SetIndices ( IDirect3DIndexBuffer9 *pIndexData );
	HRESULT GetIndices ( IDirect3DIndexBuffer9 **ppIndexData );
	HRESULT CreatePixelShader ( CONST DWORD *pFunction, IDirect3DPixelShader9 **ppShader );
	HRESULT SetPixelShader ( IDirect3DPixelShader9 *pShader );
	HRESULT GetPixelShader ( IDirect3DPixelShader9 **ppShader );
	HRESULT SetPixelShaderConstantF ( UINT StartRegister, CONST float *pConstantData, UINT Vector4fCount );
	HRESULT GetPixelShaderConstantF ( UINT StartRegister, float *pConstantData, UINT Vector4fCount );
	HRESULT SetPixelShaderConstantI ( UINT StartRegister, CONST int *pConstantData, UINT Vector4iCount );
	HRESULT GetPixelShaderConstantI ( UINT StartRegister, int *pConstantData, UINT Vector4iCount );
	HRESULT SetPixelShaderConstantB ( UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount );
	HRESULT GetPixelShaderConstantB ( UINT StartRegister, BOOL *pConstantData, UINT BoolCount );
	HRESULT DrawRectPatch ( UINT Handle, CONST float *pNumSegs, CONST D3DRECTPATCH_INFO *pRectPatchInfo );
	HRESULT DrawTriPatch ( UINT Handle, CONST float *pNumSegs, CONST D3DTRIPATCH_INFO *pTriPatchInfo );
	HRESULT DeletePatch ( UINT Handle );
	HRESULT CreateQuery ( D3DQUERYTYPE Type, IDirect3DQuery9 **ppQuery );

private:
	IDirect3DDevice9* _dx = nullptr;
	bool              _hook = false;
};

#endif // DIRECTX_H
