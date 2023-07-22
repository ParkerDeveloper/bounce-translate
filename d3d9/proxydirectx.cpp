#include "proxydirectx.h"
#include <QList>
#include "GirlCursor.hpp"

static IDirect3DDevice9* origIDirect3DDevice9 = static_cast<IDirect3DDevice9*>(nullptr);
static QList<CD3DFont*> fontList;
static QList<CD3DRender*> renderList;
static QList<SRTexture*> textureList;
static SRTexture* pGirlCursor;
static bool hasGirlCursorDraw = false;

proxyIDirect3DDevice9::proxyIDirect3DDevice9 ( IDirect3DDevice9 *pOriginal )
{
	origIDirect3DDevice9 = pOriginal;
}

proxyIDirect3DDevice9::~proxyIDirect3DDevice9 ( void )
{
	if (*reinterpret_cast<IDirect3DDevice9 **>(0xC97C28) == this)
		*reinterpret_cast<IDirect3DDevice9 **>(0xC97C28) = origIDirect3DDevice9;
	foreach (auto pFont, fontList) {
		if (pFont != nullptr){
			pFont->Invalidate();
			delete pFont;
		}
	}
	foreach (auto pRender, renderList) {
		if (pRender != nullptr){
			pRender->Invalidate();
			delete pRender;
		}
	}
	foreach (auto pTexture, textureList) {
		if (pTexture != nullptr){
			pTexture->Release();
			delete pTexture;
		}
	}

	fontList.clear();
	renderList.clear();
	textureList.clear();
}

HRESULT proxyIDirect3DDevice9::QueryInterface ( REFIID riid, void **ppvObj )
{
	HRESULT hRes = g_class.DirectX->__d3d9_QueryInterface(riid, ppvObj);

	*ppvObj = NULL;
	if (!g_class.DirectX->__d3d9_isHooked())
		hRes = origIDirect3DDevice9->QueryInterface( riid, ppvObj );
	if ( hRes == NOERROR )
		*ppvObj = this;

	return hRes;
}

ULONG proxyIDirect3DDevice9::AddRef ( void )
{
	ULONG result = g_class.DirectX->__d3d9_AddRef();
	if (!g_class.DirectX->__d3d9_isHooked())
		return origIDirect3DDevice9->AddRef();
	return result;
}

ULONG proxyIDirect3DDevice9::Release ( void )
{
	ULONG	count = g_class.DirectX->__d3d9_Release();
	if (!g_class.DirectX->__d3d9_isHooked())
		count = origIDirect3DDevice9->Release();

	if ( count == 0 )
	{
		delete( this );
	}

	return count;
}

HRESULT proxyIDirect3DDevice9::TestCooperativeLevel ( void )
{
	HRESULT result = g_class.DirectX->__d3d9_TestCooperativeLevel();
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->TestCooperativeLevel();
}

UINT proxyIDirect3DDevice9::GetAvailableTextureMem ( void )
{
	UINT result = g_class.DirectX->__d3d9_GetAvailableTextureMem();
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetAvailableTextureMem();
}

HRESULT proxyIDirect3DDevice9::EvictManagedResources ( void )
{
	HRESULT result = g_class.DirectX->__d3d9_EvictManagedResources();
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->EvictManagedResources();
}

HRESULT proxyIDirect3DDevice9::GetDirect3D ( IDirect3D9 **ppD3D9 )
{
	HRESULT result = g_class.DirectX->__d3d9_GetDirect3D(ppD3D9);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetDirect3D( ppD3D9 );
}

HRESULT proxyIDirect3DDevice9::GetDeviceCaps ( D3DCAPS9 *pCaps )
{
	HRESULT result = g_class.DirectX->__d3d9_GetDeviceCaps(pCaps);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetDeviceCaps( pCaps );
}

HRESULT proxyIDirect3DDevice9::GetDisplayMode ( UINT iSwapChain, D3DDISPLAYMODE
												*pMode )
{
	HRESULT result = g_class.DirectX->__d3d9_GetDisplayMode(iSwapChain, pMode);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetDisplayMode( iSwapChain, pMode );
}

HRESULT proxyIDirect3DDevice9::GetCreationParameters (
		D3DDEVICE_CREATION_PARAMETERS *pParameters )
{
	HRESULT result = g_class.DirectX->__d3d9_GetCreationParameters(pParameters);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetCreationParameters( pParameters );
}

HRESULT proxyIDirect3DDevice9::SetCursorProperties ( UINT XHotSpot, UINT
													 YHotSpot, IDirect3DSurface9 *pCursorBitmap )
{
	HRESULT result = g_class.DirectX->__d3d9_SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetCursorProperties( XHotSpot, YHotSpot,
													  pCursorBitmap );
}

void proxyIDirect3DDevice9::SetCursorPosition ( int X, int Y, DWORD Flags )
{
	g_class.DirectX->__d3d9_SetCursorPosition(X, Y, Flags);
	if (g_class.DirectX->__d3d9_isHooked())
		return;
	origIDirect3DDevice9->SetCursorPosition( X, Y, Flags );
}

BOOL proxyIDirect3DDevice9::ShowCursor ( BOOL bShow )
{
	BOOL result = g_class.DirectX->__d3d9_ShowCursor(bShow);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->ShowCursor( bShow );
}

HRESULT proxyIDirect3DDevice9::CreateAdditionalSwapChain ( D3DPRESENT_PARAMETERS
														   *pPresentationParameters,
														   IDirect3DSwapChain9
														   **pSwapChain )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateAdditionalSwapChain(
				pPresentationParameters, pSwapChain );
}

HRESULT proxyIDirect3DDevice9::GetSwapChain ( UINT iSwapChain,
											  IDirect3DSwapChain9 **pSwapChain )
{
	HRESULT result = g_class.DirectX->__d3d9_GetSwapChain(iSwapChain, pSwapChain);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetSwapChain( iSwapChain, pSwapChain );
}

UINT proxyIDirect3DDevice9::GetNumberOfSwapChains ( void )
{
	UINT result = g_class.DirectX->__d3d9_GetNumberOfSwapChains();
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetNumberOfSwapChains();
}

HRESULT proxyIDirect3DDevice9::Reset ( D3DPRESENT_PARAMETERS
									   *pPresentationParameters )
{
	foreach (auto pFont, fontList) {
		if (pFont != nullptr)
			pFont->Invalidate();
		else fontList.removeOne(pFont);
	}
	foreach (auto pRender, renderList) {
		if (pRender != nullptr)
			pRender->Invalidate();
		else renderList.removeOne(pRender);
	}
	foreach (auto pTexture, textureList) {
		if (pTexture != nullptr)
			pTexture->Release();
		else textureList.removeOne(pTexture);
	}
	hasGirlCursorDraw = false;

	// always attempt to reset orig device if we are asked to
	// since GTA is getting the state of the original device
	HRESULT hRes_orig_Reset;
	hRes_orig_Reset = g_class.DirectX->__d3d9_Reset(pPresentationParameters);
	if (!g_class.DirectX->__d3d9_isHooked())
		hRes_orig_Reset = origIDirect3DDevice9->Reset( pPresentationParameters );

	// handle the return from original Reset()
	if ( hRes_orig_Reset == D3D_OK ) {
		foreach (auto pFont, fontList) {
			pFont->Initialize(origIDirect3DDevice9);
		}
		foreach (auto pRender, renderList) {
			pRender->Initialize(origIDirect3DDevice9);
		}
		foreach (auto pTexture, textureList) {
			pTexture->Initialize(origIDirect3DDevice9);
		}
	}

	// bai
	return hRes_orig_Reset;
}

HRESULT proxyIDirect3DDevice9::Present ( CONST RECT *pSourceRect, CONST RECT
										 *pDestRect, HWND hDestWindowOverride,
										 CONST RGNDATA *pDirtyRegion )
{
	// A fog flicker fix for some ATI cards
	// this is screwing up right not for some reason
	// check out the other pD3DData references for an idea of what this does
	//
	//D3DMATRIX projMatrix;
	//pD3DData->GetTransform ( D3DTS_PROJECTION, &projMatrix );
	//origIDirect3DDevice9->SetTransform ( D3DTS_PROJECTION, &projMatrix );

	static bool initialize = false;
	if (!initialize){
		initialize = true;
		pGirlCursor = new SRTexture(330, 470);
		RegisterTexture(pGirlCursor);
		pGirlCursor->Load(resource::Cursor_png::addres(), resource::Cursor_png::size);
	}

	if (!hasGirlCursorDraw){
		pGirlCursor->Begin();
		pGirlCursor->Clear();
		pGirlCursor->End();
		hasGirlCursorDraw = true;
	}

	HRESULT result = g_class.DirectX->__d3d9_Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	if ( !g_vars.isMenuOpened )
		for ( auto pMenu : MenuList )
			if ( pMenu->isInizialize() && pMenu->isShowed() )
				pMenu->onDraw();
	if (cursorType == eCursorType::Girl &&
		g_class.samp->misc()->iCursorMode	&&
		g_vars.isLocalCursorShowed			){
		POINT M;
		GetCursorPos( &M );
		ScreenToClient( g_vars.hwnd, &M );
		pGirlCursor->Render(M.x, M.y - 101 / 5, 330 / 5, 470 / 5);
	} else if (!g_class.samp->misc()->iCursorMode)
		g_vars.isLocalCursorShowed = false;

	// get original function to return
	if (!g_class.DirectX->__d3d9_isHooked())
		return origIDirect3DDevice9->Present( pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
	else return result;
}

HRESULT proxyIDirect3DDevice9::GetBackBuffer ( UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type,
											   IDirect3DSurface9 **ppBackBuffer )
{
	HRESULT result = g_class.DirectX->__d3d9_GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetBackBuffer( iSwapChain, iBackBuffer, Type, ppBackBuffer );
}

HRESULT proxyIDirect3DDevice9::GetRasterStatus ( UINT iSwapChain, D3DRASTER_STATUS *pRasterStatus )
{
	HRESULT result = g_class.DirectX->__d3d9_GetRasterStatus(iSwapChain, pRasterStatus);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetRasterStatus( iSwapChain, pRasterStatus );
}

HRESULT proxyIDirect3DDevice9::SetDialogBoxMode ( BOOL bEnableDialogs )
{
	HRESULT result = g_class.DirectX->__d3d9_SetDialogBoxMode(bEnableDialogs);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetDialogBoxMode( bEnableDialogs );
}

void proxyIDirect3DDevice9::SetGammaRamp ( UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP *pRamp )
{
	g_class.DirectX->__d3d9_SetGammaRamp(iSwapChain, Flags, pRamp);
	if (g_class.DirectX->__d3d9_isHooked())
		return;
	origIDirect3DDevice9->SetGammaRamp( iSwapChain, Flags, pRamp );
}

void proxyIDirect3DDevice9::GetGammaRamp ( UINT iSwapChain, D3DGAMMARAMP *pRamp )
{
	g_class.DirectX->__d3d9_GetGammaRamp(iSwapChain, pRamp);
	if (g_class.DirectX->__d3d9_isHooked())
		return;
	origIDirect3DDevice9->GetGammaRamp( iSwapChain, pRamp );
}

HRESULT proxyIDirect3DDevice9::CreateTexture ( UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format,
											   D3DPOOL Pool, IDirect3DTexture9 **ppTexture, HANDLE *pSharedHandle )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateTexture( Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateVolumeTexture ( UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage,
													 D3DFORMAT Format, D3DPOOL Pool,
													 IDirect3DVolumeTexture9 **ppVolumeTexture, HANDLE *pSharedHandle )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateVolumeTexture( Width, Height, Depth, Levels, Usage, Format, Pool,
													  ppVolumeTexture, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateCubeTexture ( UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format,
												   D3DPOOL Pool, IDirect3DCubeTexture9 **ppCubeTexture,
												   HANDLE *pSharedHandle )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateCubeTexture( EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture,
													pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateVertexBuffer ( UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool,
													IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateVertexBuffer( Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateIndexBuffer ( UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
												   IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateIndexBuffer( Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateRenderTarget ( UINT Width, UINT Height, D3DFORMAT Format,
													D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality,
													BOOL Lockable, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateRenderTarget( Width, Height, Format, MultiSample, MultisampleQuality, Lockable,
													 ppSurface, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateDepthStencilSurface ( UINT Width, UINT Height, D3DFORMAT Format,
														   D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality,
														   BOOL Discard, IDirect3DSurface9 **ppSurface,
														   HANDLE *pSharedHandle )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateDepthStencilSurface( Width, Height, Format, MultiSample, MultisampleQuality,
															Discard, ppSurface, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::UpdateSurface ( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect,
											   IDirect3DSurface9 *pDestinationSurface, CONST POINT *pDestPoint )
{
	HRESULT result = g_class.DirectX->__d3d9_UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->UpdateSurface( pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint );
}

HRESULT proxyIDirect3DDevice9::UpdateTexture ( IDirect3DBaseTexture9 *pSourceTexture,
											   IDirect3DBaseTexture9 *pDestinationTexture )
{
	HRESULT result = g_class.DirectX->__d3d9_UpdateTexture(pSourceTexture, pDestinationTexture);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->UpdateTexture( pSourceTexture, pDestinationTexture );
}

HRESULT proxyIDirect3DDevice9::GetRenderTargetData ( IDirect3DSurface9 *pRenderTarget, IDirect3DSurface9 *pDestSurface )
{
	HRESULT result = g_class.DirectX->__d3d9_GetRenderTargetData(pRenderTarget, pDestSurface);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetRenderTargetData( pRenderTarget, pDestSurface );
}

HRESULT proxyIDirect3DDevice9::GetFrontBufferData ( UINT iSwapChain, IDirect3DSurface9 *pDestSurface )
{
	HRESULT result = g_class.DirectX->__d3d9_GetFrontBufferData(iSwapChain, pDestSurface);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetFrontBufferData( iSwapChain, pDestSurface );
}

HRESULT proxyIDirect3DDevice9::StretchRect ( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect,
											 IDirect3DSurface9 *pDestSurface, CONST RECT *pDestRect,
											 D3DTEXTUREFILTERTYPE Filter )
{
	HRESULT result = g_class.DirectX->__d3d9_StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->StretchRect( pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter );
}

HRESULT proxyIDirect3DDevice9::ColorFill ( IDirect3DSurface9 *pSurface, CONST RECT *pRect, D3DCOLOR color )
{
	HRESULT result = g_class.DirectX->__d3d9_ColorFill(pSurface, pRect, color);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->ColorFill( pSurface, pRect, color );
}

HRESULT proxyIDirect3DDevice9::CreateOffscreenPlainSurface ( UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool,
															 IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateOffscreenPlainSurface( Width, Height, Format, Pool, ppSurface, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::SetRenderTarget ( DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget )
{
	HRESULT result = g_class.DirectX->__d3d9_SetRenderTarget(RenderTargetIndex, pRenderTarget);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetRenderTarget( RenderTargetIndex, pRenderTarget );
}

HRESULT proxyIDirect3DDevice9::GetRenderTarget ( DWORD RenderTargetIndex, IDirect3DSurface9 **ppRenderTarget )
{
	HRESULT result = g_class.DirectX->__d3d9_GetRenderTarget(RenderTargetIndex, ppRenderTarget);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetRenderTarget( RenderTargetIndex, ppRenderTarget );
}

HRESULT proxyIDirect3DDevice9::SetDepthStencilSurface ( IDirect3DSurface9 *pNewZStencil )
{
	HRESULT result = g_class.DirectX->__d3d9_SetDepthStencilSurface(pNewZStencil);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetDepthStencilSurface( pNewZStencil );
}

HRESULT proxyIDirect3DDevice9::GetDepthStencilSurface ( IDirect3DSurface9 **ppZStencilSurface )
{
	HRESULT result = g_class.DirectX->__d3d9_GetDepthStencilSurface(ppZStencilSurface);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetDepthStencilSurface( ppZStencilSurface );
}

HRESULT proxyIDirect3DDevice9::BeginScene ( void )
{
	HRESULT result = g_class.DirectX->__d3d9_BeginScene();
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	// return original function
	return origIDirect3DDevice9->BeginScene();
}

HRESULT proxyIDirect3DDevice9::EndScene ( void )
{
	HRESULT result = g_class.DirectX->__d3d9_EndScene();
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->EndScene();
}

HRESULT proxyIDirect3DDevice9::Clear ( DWORD Count, CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z,
									   DWORD Stencil )
{
	HRESULT result = g_class.DirectX->__d3d9_Clear(Count, pRects, Flags, Color, Z, Stencil);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->Clear( Count, pRects, Flags, Color, Z, Stencil );
}

HRESULT proxyIDirect3DDevice9::SetTransform ( D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix )
{
	HRESULT result = g_class.DirectX->__d3d9_SetTransform(State, pMatrix);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetTransform( State, pMatrix );
}

HRESULT proxyIDirect3DDevice9::GetTransform ( D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix )
{
	HRESULT result = g_class.DirectX->__d3d9_GetTransform(State, pMatrix);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetTransform( State, pMatrix );
}

HRESULT proxyIDirect3DDevice9::MultiplyTransform ( D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix )
{
	HRESULT result = g_class.DirectX->__d3d9_MultiplyTransform(State, pMatrix);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->MultiplyTransform( State, pMatrix );
}

HRESULT proxyIDirect3DDevice9::SetViewport ( CONST D3DVIEWPORT9 *pViewport )
{
	HRESULT result = g_class.DirectX->__d3d9_SetViewport(pViewport);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetViewport( pViewport );
}

HRESULT proxyIDirect3DDevice9::GetViewport ( D3DVIEWPORT9 *pViewport )
{
	HRESULT result = g_class.DirectX->__d3d9_GetViewport(pViewport);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetViewport( pViewport );
}

HRESULT proxyIDirect3DDevice9::SetMaterial ( CONST D3DMATERIAL9 *pMaterial )
{
	HRESULT result = g_class.DirectX->__d3d9_SetMaterial(pMaterial);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetMaterial( pMaterial );
}

HRESULT proxyIDirect3DDevice9::GetMaterial ( D3DMATERIAL9 *pMaterial )
{
	HRESULT result = g_class.DirectX->__d3d9_GetMaterial(pMaterial);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetMaterial( pMaterial );
}

HRESULT proxyIDirect3DDevice9::SetLight ( DWORD Index, CONST D3DLIGHT9 *pLight )
{
	HRESULT result = g_class.DirectX->__d3d9_SetLight(Index, pLight);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetLight( Index, pLight );
}

HRESULT proxyIDirect3DDevice9::GetLight ( DWORD Index, D3DLIGHT9 *pLight )
{
	HRESULT result = g_class.DirectX->__d3d9_GetLight(Index, pLight);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetLight( Index, pLight );
}

HRESULT proxyIDirect3DDevice9::LightEnable ( DWORD Index, BOOL Enable )
{
	HRESULT result = g_class.DirectX->__d3d9_LightEnable(Index, Enable);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->LightEnable( Index, Enable );
}

HRESULT proxyIDirect3DDevice9::GetLightEnable ( DWORD Index, BOOL *pEnable )
{
	HRESULT result = g_class.DirectX->__d3d9_GetLightEnable(Index, pEnable);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetLightEnable( Index, pEnable );
}

HRESULT proxyIDirect3DDevice9::SetClipPlane ( DWORD Index, CONST float *pPlane )
{
	HRESULT result = g_class.DirectX->__d3d9_SetClipPlane(Index, pPlane);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetClipPlane( Index, pPlane );
}

HRESULT proxyIDirect3DDevice9::GetClipPlane ( DWORD Index, float *pPlane )
{
	HRESULT result = g_class.DirectX->__d3d9_GetClipPlane(Index, pPlane);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetClipPlane( Index, pPlane );
}

HRESULT proxyIDirect3DDevice9::SetRenderState ( D3DRENDERSTATETYPE State, DWORD Value )
{
	HRESULT result = g_class.DirectX->__d3d9_SetRenderState(State, Value);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetRenderState( State, Value );
}

HRESULT proxyIDirect3DDevice9::GetRenderState ( D3DRENDERSTATETYPE State, DWORD *pValue )
{
	HRESULT result = g_class.DirectX->__d3d9_GetRenderState(State, pValue);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetRenderState( State, pValue );
}

HRESULT proxyIDirect3DDevice9::CreateStateBlock ( D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9 **ppSB )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateStateBlock(Type, ppSB);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateStateBlock( Type, ppSB );
}

HRESULT proxyIDirect3DDevice9::BeginStateBlock ( void )
{
	HRESULT result = g_class.DirectX->__d3d9_BeginStateBlock();
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->BeginStateBlock();
}

HRESULT proxyIDirect3DDevice9::EndStateBlock ( IDirect3DStateBlock9 **ppSB )
{
	HRESULT result = g_class.DirectX->__d3d9_EndStateBlock(ppSB);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->EndStateBlock( ppSB );
}

HRESULT proxyIDirect3DDevice9::SetClipStatus ( CONST D3DCLIPSTATUS9 *pClipStatus )
{
	HRESULT result = g_class.DirectX->__d3d9_SetClipStatus(pClipStatus);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetClipStatus( pClipStatus );
}

HRESULT proxyIDirect3DDevice9::GetClipStatus ( D3DCLIPSTATUS9 *pClipStatus )
{
	HRESULT result = g_class.DirectX->__d3d9_GetClipStatus(pClipStatus);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetClipStatus( pClipStatus );
}

HRESULT proxyIDirect3DDevice9::GetTexture ( DWORD Stage, IDirect3DBaseTexture9 **ppTexture )
{
	HRESULT result = g_class.DirectX->__d3d9_GetTexture(Stage, ppTexture);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetTexture( Stage, ppTexture );
}

HRESULT proxyIDirect3DDevice9::SetTexture ( DWORD Stage, IDirect3DBaseTexture9 *pTexture )
{
	HRESULT result = g_class.DirectX->__d3d9_SetTexture(Stage, pTexture);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetTexture( Stage, pTexture );
}

HRESULT proxyIDirect3DDevice9::GetTextureStageState ( DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue )
{
	HRESULT result = g_class.DirectX->__d3d9_GetTextureStageState(Stage, Type, pValue);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetTextureStageState( Stage, Type, pValue );
}

HRESULT proxyIDirect3DDevice9::SetTextureStageState ( DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value )
{
	HRESULT result = g_class.DirectX->__d3d9_SetTextureStageState(Stage, Type, Value);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetTextureStageState( Stage, Type, Value );
}

HRESULT proxyIDirect3DDevice9::GetSamplerState ( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD *pValue )
{
	HRESULT result = g_class.DirectX->__d3d9_GetSamplerState(Sampler, Type, pValue);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetSamplerState( Sampler, Type, pValue );
}

HRESULT proxyIDirect3DDevice9::SetSamplerState ( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value )
{
	HRESULT result = g_class.DirectX->__d3d9_SetSamplerState(Sampler, Type, Value);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetSamplerState( Sampler, Type, Value );
}

HRESULT proxyIDirect3DDevice9::ValidateDevice ( DWORD *pNumPasses )
{
	HRESULT result = g_class.DirectX->__d3d9_ValidateDevice(pNumPasses);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->ValidateDevice( pNumPasses );
}

HRESULT proxyIDirect3DDevice9::SetPaletteEntries ( UINT PaletteNumber, CONST PALETTEENTRY *pEntries )
{
	HRESULT result = g_class.DirectX->__d3d9_SetPaletteEntries(PaletteNumber, pEntries);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetPaletteEntries( PaletteNumber, pEntries );
}

HRESULT proxyIDirect3DDevice9::GetPaletteEntries ( UINT PaletteNumber, PALETTEENTRY *pEntries )
{
	HRESULT result = g_class.DirectX->__d3d9_GetPaletteEntries(PaletteNumber, pEntries);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetPaletteEntries( PaletteNumber, pEntries );
}

HRESULT proxyIDirect3DDevice9::SetCurrentTexturePalette ( UINT PaletteNumber )
{
	HRESULT result = g_class.DirectX->__d3d9_SetCurrentTexturePalette(PaletteNumber);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetCurrentTexturePalette( PaletteNumber );
}

HRESULT proxyIDirect3DDevice9::GetCurrentTexturePalette ( UINT *PaletteNumber )
{
	HRESULT result = g_class.DirectX->__d3d9_GetCurrentTexturePalette(PaletteNumber);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetCurrentTexturePalette( PaletteNumber );
}

HRESULT proxyIDirect3DDevice9::SetScissorRect ( CONST RECT *pRect )
{
	HRESULT result = g_class.DirectX->__d3d9_SetScissorRect(pRect);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetScissorRect( pRect );
}

HRESULT proxyIDirect3DDevice9::GetScissorRect ( RECT *pRect )
{
	HRESULT result = g_class.DirectX->__d3d9_GetScissorRect(pRect);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetScissorRect( pRect );
}

HRESULT proxyIDirect3DDevice9::SetSoftwareVertexProcessing ( BOOL bSoftware )
{
	HRESULT result = g_class.DirectX->__d3d9_SetSoftwareVertexProcessing(bSoftware);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetSoftwareVertexProcessing( bSoftware );
}

BOOL proxyIDirect3DDevice9::GetSoftwareVertexProcessing ( void )
{
	BOOL result = g_class.DirectX->__d3d9_GetSoftwareVertexProcessing();
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetSoftwareVertexProcessing();
}

HRESULT proxyIDirect3DDevice9::SetNPatchMode ( float nSegments )
{
	HRESULT result = g_class.DirectX->__d3d9_SetNPatchMode(nSegments);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetNPatchMode( nSegments );
}

float proxyIDirect3DDevice9::GetNPatchMode ( void )
{
	float result = g_class.DirectX->__d3d9_GetNPatchMode();
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetNPatchMode();
}

HRESULT proxyIDirect3DDevice9::DrawPrimitive ( D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount )
{
	HRESULT result = g_class.DirectX->__d3d9_DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->DrawPrimitive( PrimitiveType, StartVertex, PrimitiveCount );
}

HRESULT proxyIDirect3DDevice9::DrawIndexedPrimitive ( D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex,
													  UINT MinVertexIndex, UINT NumVertices, UINT startIndex,
													  UINT primCount )
{
	HRESULT result = g_class.DirectX->__d3d9_DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->DrawIndexedPrimitive( PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices,
													   startIndex, primCount );
}

HRESULT proxyIDirect3DDevice9::DrawPrimitiveUP ( D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount,
												 CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride )
{
	HRESULT result = g_class.DirectX->__d3d9_DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->DrawPrimitiveUP( PrimitiveType, PrimitiveCount, pVertexStreamZeroData,
												  VertexStreamZeroStride );
}

HRESULT proxyIDirect3DDevice9::DrawIndexedPrimitiveUP ( D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex,
														UINT NumVertices, UINT PrimitiveCount, CONST void *pIndexData,
														D3DFORMAT IndexDataFormat, CONST void *pVertexStreamZeroData,
														UINT VertexStreamZeroStride )
{
	HRESULT result = g_class.DirectX->__d3d9_DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->DrawIndexedPrimitiveUP( PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount,
														 pIndexData, IndexDataFormat, pVertexStreamZeroData,
														 VertexStreamZeroStride );
}

HRESULT proxyIDirect3DDevice9::ProcessVertices ( UINT SrcStartIndex, UINT DestIndex, UINT VertexCount,
												 IDirect3DVertexBuffer9 *pDestBuffer,
												 IDirect3DVertexDeclaration9 *pVertexDecl, DWORD Flags )
{
	HRESULT result = g_class.DirectX->__d3d9_ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->ProcessVertices( SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags );
}

HRESULT proxyIDirect3DDevice9::CreateVertexDeclaration ( CONST D3DVERTEXELEMENT9 *pVertexElements,
														 IDirect3DVertexDeclaration9 **ppDecl )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateVertexDeclaration(pVertexElements, ppDecl);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateVertexDeclaration( pVertexElements, ppDecl );
}

HRESULT proxyIDirect3DDevice9::SetVertexDeclaration ( IDirect3DVertexDeclaration9 *pDecl )
{
	HRESULT result = g_class.DirectX->__d3d9_SetVertexDeclaration(pDecl);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetVertexDeclaration( pDecl );
}

HRESULT proxyIDirect3DDevice9::GetVertexDeclaration ( IDirect3DVertexDeclaration9 **ppDecl )
{
	HRESULT result = g_class.DirectX->__d3d9_GetVertexDeclaration(ppDecl);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetVertexDeclaration( ppDecl );
}

HRESULT proxyIDirect3DDevice9::SetFVF ( DWORD FVF )
{
	HRESULT result = g_class.DirectX->__d3d9_SetFVF(FVF);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetFVF( FVF );
}

HRESULT proxyIDirect3DDevice9::GetFVF ( DWORD *pFVF )
{
	HRESULT result = g_class.DirectX->__d3d9_GetFVF(pFVF);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetFVF( pFVF );
}

HRESULT proxyIDirect3DDevice9::CreateVertexShader ( CONST DWORD *pFunction, IDirect3DVertexShader9 **ppShader )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateVertexShader(pFunction, ppShader);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateVertexShader( pFunction, ppShader );
}

HRESULT proxyIDirect3DDevice9::SetVertexShader ( IDirect3DVertexShader9 *pShader )
{
	HRESULT result = g_class.DirectX->__d3d9_SetVertexShader(pShader);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetVertexShader( pShader );
}

HRESULT proxyIDirect3DDevice9::GetVertexShader ( IDirect3DVertexShader9 **ppShader )
{
	HRESULT result = g_class.DirectX->__d3d9_GetVertexShader(ppShader);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetVertexShader( ppShader );
}

HRESULT proxyIDirect3DDevice9::SetVertexShaderConstantF ( UINT StartRegister, CONST float *pConstantData,
														  UINT Vector4fCount )
{
	HRESULT result = g_class.DirectX->__d3d9_SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetVertexShaderConstantF( StartRegister, pConstantData, Vector4fCount );
}

HRESULT proxyIDirect3DDevice9::GetVertexShaderConstantF ( UINT StartRegister, float *pConstantData, UINT Vector4fCount )
{
	HRESULT result = g_class.DirectX->__d3d9_GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetVertexShaderConstantF( StartRegister, pConstantData, Vector4fCount );
}

HRESULT proxyIDirect3DDevice9::SetVertexShaderConstantI ( UINT StartRegister, CONST int *pConstantData,
														  UINT Vector4iCount )
{
	HRESULT result = g_class.DirectX->__d3d9_SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetVertexShaderConstantI( StartRegister, pConstantData, Vector4iCount );
}

HRESULT proxyIDirect3DDevice9::GetVertexShaderConstantI ( UINT StartRegister, int *pConstantData, UINT Vector4iCount )
{
	HRESULT result = g_class.DirectX->__d3d9_GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetVertexShaderConstantI( StartRegister, pConstantData, Vector4iCount );
}

HRESULT proxyIDirect3DDevice9::SetVertexShaderConstantB ( UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount )
{
	HRESULT result = g_class.DirectX->__d3d9_SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetVertexShaderConstantB( StartRegister, pConstantData, BoolCount );
}

HRESULT proxyIDirect3DDevice9::GetVertexShaderConstantB ( UINT StartRegister, BOOL *pConstantData, UINT BoolCount )
{
	HRESULT result = g_class.DirectX->__d3d9_GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetVertexShaderConstantB( StartRegister, pConstantData, BoolCount );
}

HRESULT proxyIDirect3DDevice9::SetStreamSource ( UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData,
												 UINT OffsetInBytes, UINT Stride )
{
	HRESULT result = g_class.DirectX->__d3d9_SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetStreamSource( StreamNumber, pStreamData, OffsetInBytes, Stride );
}

HRESULT proxyIDirect3DDevice9::GetStreamSource ( UINT StreamNumber, IDirect3DVertexBuffer9 **ppStreamData,
												 UINT *OffsetInBytes, UINT *pStride )
{
	HRESULT result = g_class.DirectX->__d3d9_GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetStreamSource( StreamNumber, ppStreamData, OffsetInBytes, pStride );
}

HRESULT proxyIDirect3DDevice9::SetStreamSourceFreq ( UINT StreamNumber, UINT Divider )
{
	HRESULT result = g_class.DirectX->__d3d9_SetStreamSourceFreq(StreamNumber, Divider);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetStreamSourceFreq( StreamNumber, Divider );
}

HRESULT proxyIDirect3DDevice9::GetStreamSourceFreq ( UINT StreamNumber, UINT *Divider )
{
	HRESULT result = g_class.DirectX->__d3d9_GetStreamSourceFreq(StreamNumber, Divider);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetStreamSourceFreq( StreamNumber, Divider );
}

HRESULT proxyIDirect3DDevice9::SetIndices ( IDirect3DIndexBuffer9 *pIndexData )
{
	HRESULT result = g_class.DirectX->__d3d9_SetIndices(pIndexData);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetIndices( pIndexData );
}

HRESULT proxyIDirect3DDevice9::GetIndices ( IDirect3DIndexBuffer9 **ppIndexData )
{
	HRESULT result = g_class.DirectX->__d3d9_GetIndices(ppIndexData);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetIndices( ppIndexData );
}

HRESULT proxyIDirect3DDevice9::CreatePixelShader ( CONST DWORD *pFunction, IDirect3DPixelShader9 **ppShader )
{
	HRESULT result = g_class.DirectX->__d3d9_CreatePixelShader(pFunction, ppShader);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreatePixelShader( pFunction, ppShader );
}

HRESULT proxyIDirect3DDevice9::SetPixelShader ( IDirect3DPixelShader9 *pShader )
{
	HRESULT result = g_class.DirectX->__d3d9_SetPixelShader(pShader);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetPixelShader( pShader );
}

HRESULT proxyIDirect3DDevice9::GetPixelShader ( IDirect3DPixelShader9 **ppShader )
{
	HRESULT result = g_class.DirectX->__d3d9_GetPixelShader(ppShader);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetPixelShader( ppShader );
}

HRESULT proxyIDirect3DDevice9::SetPixelShaderConstantF ( UINT StartRegister, CONST float *pConstantData,
														 UINT Vector4fCount )
{
	HRESULT result = g_class.DirectX->__d3d9_SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetPixelShaderConstantF( StartRegister, pConstantData, Vector4fCount );
}

HRESULT proxyIDirect3DDevice9::GetPixelShaderConstantF ( UINT StartRegister, float *pConstantData, UINT Vector4fCount )
{
	HRESULT result = g_class.DirectX->__d3d9_GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetPixelShaderConstantF( StartRegister, pConstantData, Vector4fCount );
}

HRESULT proxyIDirect3DDevice9::SetPixelShaderConstantI ( UINT StartRegister, CONST int *pConstantData, UINT Vector4iCount )
{
	HRESULT result = g_class.DirectX->__d3d9_SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetPixelShaderConstantI( StartRegister, pConstantData, Vector4iCount );
}

HRESULT proxyIDirect3DDevice9::GetPixelShaderConstantI ( UINT StartRegister, int *pConstantData, UINT Vector4iCount )
{
	HRESULT result = g_class.DirectX->__d3d9_GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetPixelShaderConstantI( StartRegister, pConstantData, Vector4iCount );
}

HRESULT proxyIDirect3DDevice9::SetPixelShaderConstantB ( UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount )
{
	HRESULT result = g_class.DirectX->__d3d9_SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->SetPixelShaderConstantB( StartRegister, pConstantData, BoolCount );
}

HRESULT proxyIDirect3DDevice9::GetPixelShaderConstantB ( UINT StartRegister, BOOL *pConstantData, UINT BoolCount )
{
	HRESULT result = g_class.DirectX->__d3d9_GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->GetPixelShaderConstantB( StartRegister, pConstantData, BoolCount );
}

HRESULT proxyIDirect3DDevice9::DrawRectPatch ( UINT Handle, CONST float *pNumSegs, CONST D3DRECTPATCH_INFO *pRectPatchInfo )
{
	HRESULT result = g_class.DirectX->__d3d9_DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->DrawRectPatch( Handle, pNumSegs, pRectPatchInfo );
}

HRESULT proxyIDirect3DDevice9::DrawTriPatch ( UINT Handle, CONST float *pNumSegs, CONST D3DTRIPATCH_INFO *pTriPatchInfo )
{
	HRESULT result = g_class.DirectX->__d3d9_DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->DrawTriPatch( Handle, pNumSegs, pTriPatchInfo );
}

HRESULT proxyIDirect3DDevice9::DeletePatch ( UINT Handle )
{
	HRESULT result = g_class.DirectX->__d3d9_DeletePatch(Handle);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->DeletePatch( Handle );
}

HRESULT proxyIDirect3DDevice9::CreateQuery ( D3DQUERYTYPE Type, IDirect3DQuery9 **ppQuery )
{
	HRESULT result = g_class.DirectX->__d3d9_CreateQuery(Type, ppQuery);
	if (g_class.DirectX->__d3d9_isHooked())
		return result;
	return origIDirect3DDevice9->CreateQuery( Type, ppQuery );
}

void proxyIDirect3DDevice9::RegisterFont( CD3DFont *pFont )
{
	fontList.push_back(pFont);
	pFont->Initialize(this);
}

void proxyIDirect3DDevice9::ReleaseFont( CD3DFont *pFont, bool autoDelete )
{
	pFont->Invalidate();
	fontList.removeOne(pFont);
	if (autoDelete)
		delete pFont;
}

void proxyIDirect3DDevice9::RegisterRender( CD3DRender *pRender )
{
	renderList.push_back(pRender);
	pRender->Initialize(this);
}

void proxyIDirect3DDevice9::ReleaseRender( CD3DRender *pRender, bool autoDelete )
{
	pRender->Invalidate();
	renderList.removeOne(pRender);
	if (autoDelete)
		delete pRender;
}

void proxyIDirect3DDevice9::RegisterTexture(SRTexture *pTexture)
{
	textureList.push_back(pTexture);
	pTexture->Initialize(this);
}

void proxyIDirect3DDevice9::ReleaseTexture(SRTexture *pTexture, bool autoDelete)
{
	pTexture->Release();
	textureList.removeOne(pTexture);
	if (autoDelete)
		delete pTexture;
}

HRESULT proxyIDirect3DDevice9::GenerateShader ( IDirect3DPixelShader9 **pShader, float alpha, float red, float green,
												float blue )
{
	char		szShader[256];
	ID3DXBuffer *pShaderBuffer = NULL;
	sprintf_s( szShader, sizeof(szShader), "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", red, green, blue, alpha );
	if ( FAILED(D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, 0, &pShaderBuffer, NULL)) )
	{
		return E_FAIL;
	}

	if ( FAILED(CreatePixelShader((const DWORD *)pShaderBuffer->GetBufferPointer(), pShader)) )
	{
		return E_FAIL;
	}

	return S_OK;
}

IDirect3DDevice9 *proxyIDirect3DDevice9::getOriginalDevice()
{
	return origIDirect3DDevice9;
}
