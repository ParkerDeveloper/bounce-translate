#include "texture.h"
#include <QFile>
#include <assert.h>

template<typename T>
bool safe_release(T &d){
	if (d){
		d->Release();
		d = nullptr;
		return true;
	}
	return false;
}

SRTexture::SRTexture(int width, int height, QObject *parent) : QObject(parent)
{
	this->pDevice = pDevice;
	textureSize = { width, height };
	isReleased = true;
	isRenderToTexture = false;
	kIsCalledFirstInitialize = false;
	source_bkg = eTS_none;
	render = new CD3DRender(256);
}


SRTexture::~SRTexture()
{
	if (!isReleased)
		Release();
}


void SRTexture::Release()
{
	if (isRenderToTexture)
		End();
	safe_release(pSprite);
	safe_release(pTexture);

	safe_release(pTexture_bkg);
	safe_release(DS);
	render->Invalidate();
	isReleased = true;

	emit eventReleased();
}


void SRTexture::Initialize(IDirect3DDevice9 *pDevice)
{
	if (pDevice != nullptr)
		this->pDevice = pDevice;

	if (!isReleased)
		return;

	isReleased = false;
	render->Initialize(this->pDevice);

	this->pDevice->CreateTexture(textureSize.x, textureSize.y, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture, NULL);
	pTexture->GetSurfaceLevel(0, &PP1S);
	PP1S->Release();

	this->pDevice->CreateDepthStencilSurface(textureSize.x, textureSize.y, D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, FALSE, &DS, NULL);
	D3DXCreateSprite(this->pDevice, &pSprite);

	if (source_bkg == eTS_file)
		LoadTexture(path_bkg);
	else if (source_bkg == eTS_mem)
		LoadTexture(addr_bkg, size_bkg);

	emit eventInitialized();
}

void SRTexture::LoadTexture(QString fileName)
{
	D3DXIMAGE_INFO	imgInfo;
	assert(D3DXGetImageInfoFromFileW( fileName.toStdWString().c_str(), &imgInfo ) == D3D_OK);
	textureSize_bkg.x = imgInfo.Width;
	textureSize_bkg.y = imgInfo.Height;
	assert(D3DXCreateTextureFromFileW( pDevice, fileName.toStdWString().c_str(), &pTexture_bkg ) == D3D_OK);
}

void SRTexture::LoadTexture(uint addr, uint size)
{
	D3DXIMAGE_INFO	imgInfo;
	assert(D3DXGetImageInfoFromFileInMemory( (void*)addr, size, &imgInfo ) == D3D_OK);
	textureSize_bkg.x = imgInfo.Width;
	textureSize_bkg.y = imgInfo.Height;
	assert(D3DXCreateTextureFromFileInMemory( pDevice, (void*)addr, size, &pTexture_bkg ) == D3D_OK);
}

bool SRTexture::Draw(IDirect3DTexture9 *texture, int X, int Y, int W, int H, float R)
{
	if (isReleased)
		return false;

	if (W == -1)
		W = textureSize.x;
	if (H == -1)
		H = textureSize.y;

	D3DXMATRIX		mat; //Полигоны: https://dl.prime-hack.net/1r4t4.png (как понял)
	D3DSURFACE_DESC surfDesc;
	texture->GetLevelDesc( 0, &surfDesc );

	D3DXVECTOR2 axisPos = D3DXVECTOR2(X, Y);
	D3DXVECTOR2 size(1 / (float)surfDesc.Width * (float)W, 1 / (float)surfDesc.Height * (float)H);
	D3DXVECTOR2 axisCenter = D3DXVECTOR2((W / 2), (H / 2));
	D3DXMatrixTransformation2D( &mat, NULL, 0.0f, &size, &axisCenter, R, &axisPos );

	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->SetTransform(&mat);
	pSprite->Draw(texture, NULL, NULL, NULL, -1);
	pSprite->End();

	return true;
}


void SRTexture::ReInit(const int width, const int height)
{
	Release();
	textureSize = { width, height };
	Initialize();
}


void SRTexture::Begin()
{
	if (isReleased)
		return;

	if (isRenderToTexture)
		return;

	if (!SUCCEEDED(render->BeginRender()))
		return;

	pDevice->GetRenderTarget(0, &OldRT);
	pDevice->GetDepthStencilSurface(&OldDS);

	pDevice->SetDepthStencilSurface(DS);
	pDevice->SetRenderTarget(0, PP1S);

	isRenderToTexture = true;
}


void SRTexture::End()
{
	if (isReleased)
		return;

	if (!isRenderToTexture)
		return;

	pDevice->SetRenderTarget(0, OldRT);
	pDevice->SetDepthStencilSurface(OldDS);

	safe_release(OldRT);
	safe_release(OldDS);

	render->EndRender();
	isRenderToTexture = false;
}


bool SRTexture::Clear(SRColor color)
{
	if (isReleased)
		return false;

	if (!isRenderToTexture)
		return false;

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color.argb, 1.0f, 0);

	if (source_bkg != eTS_none)
		Draw(pTexture_bkg, 0, 0);

	return true;
}

HRESULT SRTexture::Save(QString fileName)
{
	if (isReleased)
		return E_FAIL;
	return D3DXSaveTextureToFile(fileName.toStdWString().c_str(), D3DXIFF_JPG, pTexture, NULL);
}

HRESULT SRTexture::Save(ID3DXBuffer *buffer)
{
	if (isReleased)
		return E_FAIL;
	return D3DXSaveTextureToFileInMemory(&buffer, D3DXIFF_JPG, pTexture, NULL);
}

HRESULT SRTexture::Load(QString fileName)
{
	if (!QFile::exists(fileName))
		return E_FAIL;

	path_bkg = fileName;
	source_bkg = eTS_file;

	if (isReleased)
		return E_FAIL;

	ReInit(textureSize.x, textureSize.y);
	return D3D_OK;
}

HRESULT SRTexture::Load(uint addr, uint size)
{
	if (addr == 0 || size == 0)
		return E_FAIL;

	addr_bkg = addr;
	size_bkg = size;
	source_bkg = eTS_mem;

	if (isReleased)
		return E_FAIL;

	ReInit(textureSize.x, textureSize.y);
	return D3D_OK;
}

bool SRTexture::textureSizeAsBkg()
{
	if (source_bkg == eTS_none)
		return false;
	ReInit(textureSize_bkg.x, textureSize_bkg.y);
	return true;
}


bool SRTexture::Render(const int X, const int Y, int W, int H, const float R)
{
	if (isRenderToTexture)
		return false;

	if (!kIsCalledFirstInitialize){
		kIsCalledFirstInitialize = true;
		emit eventInitialized();
	}

	return Draw(pTexture, X, Y, W, H, R);
}


ID3DXSprite* SRTexture::GetSprite()
{
	if (isReleased)
		throw "Sprite is released";

	return this->pSprite;
}


IDirect3DTexture9* SRTexture::GetTexture()
{
	if (isReleased)
		throw "Texture is released";

	return this->pTexture;
}

POINT SRTexture::GetSize()
{
	return textureSize;
}

POINT SRTexture::GetSizeBkg()
{
	return textureSize_bkg;
}
