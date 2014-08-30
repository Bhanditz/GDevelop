/**

Game Develop - Tiled Sprite Extension
Copyright (c) 2012 Victor Levasseur (victorlevasseur01@orange.fr)
Copyright (c) 2013-2014 Florian Rival (Florian.Rival@gmail.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.

*/

#ifndef TILEMAPOBJECT_H
#define TILEMAPOBJECT_H
#include "GDCpp/Object.h"
#include "GDCpp/RuntimeObject.h"
#include <GDCpp/Polygon.h>
#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/VertexArray.hpp>
class SFMLTextureWrapper;
class RuntimeScene;
namespace gd { class ImageManager; }
namespace gd { class InitialInstance; }
#if defined(GD_IDE_ONLY)
namespace gd { class Project; }
namespace gd { class MainFrameWrapper; }
class wxBitmap;
class wxWindow;
#endif

class TileMap;
class TileSet;

/**
 * Proxy for the TileMap
 * Note: needed because the TileMap includes wxBitmap at edittime which is not avaible in the preview compilation.
 */
class TileMapProxy
{
public:
    TileMapProxy();
    TileMapProxy(const TileMap &tilemap);
    TileMapProxy(const TileMapProxy &other);
    ~TileMapProxy();
    TileMapProxy& operator=(const TileMapProxy &other);

    TileMap& Get();
    const TileMap& Get() const;

private:
    TileMap *m_tilemap;
};

/**
 * Proxy for the TileSet
 * Note: needed for the same reason as the TileMap
 */
class TileSetProxy
{
public:
    TileSetProxy();
    TileSetProxy(const TileSet &tileset);
    TileSetProxy(const TileSetProxy &other);
    ~TileSetProxy();
    TileSetProxy& operator=(const TileSetProxy &other);

    TileSet& Get();
    const TileSet& Get() const;

private:
    TileSet *m_tileset;
};

/**
 * TileMap Object
 */
class GD_EXTENSION_API TileMapObject : public gd::Object
{
public :

    TileMapObject(std::string name_);
    virtual ~TileMapObject() {};
    virtual gd::Object * Clone() const { return new TileMapObject(*this);}

    #if defined(GD_IDE_ONLY)
    virtual bool GenerateThumbnail(const gd::Project & project, wxBitmap & thumbnail) const;
    virtual void ExposeResources(gd::ArbitraryResourceWorker & worker);

    virtual void EditObject( wxWindow* parent, gd::Project & game_, gd::MainFrameWrapper & mainFrameWrapper_ );
    virtual void LoadResources(gd::Project & project, gd::Layout & layout);
    virtual void DrawInitialInstance(gd::InitialInstance & instance, sf::RenderTarget & renderTarget, gd::Project & project, gd::Layout & layout);
    virtual sf::Vector2f GetInitialInstanceDefaultSize(gd::InitialInstance & instance, gd::Project & project, gd::Layout & layout) const;
    #endif

    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual void SetWidth(float newWidth) {};
    virtual void SetHeight(float newHeight) {};

    TileSetProxy tileSet;
    TileMapProxy tileMap;
    std::string textureName;

private:

    virtual void DoUnserializeFrom(gd::Project & project, const gd::SerializerElement & element);
    #if defined(GD_IDE_ONLY)
    virtual void DoSerializeTo(gd::SerializerElement & element) const;
    #endif

    sf::VertexArray vertexArray;
};

class GD_EXTENSION_API RuntimeTileMapObject : public RuntimeObject
{

public :

    RuntimeTileMapObject(RuntimeScene & scene, const gd::Object & object);
    virtual ~RuntimeTileMapObject() {};
    virtual RuntimeObject * Clone() const { return new RuntimeTileMapObject(*this);}

    virtual bool Draw(sf::RenderTarget & renderTarget);

    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual float GetAngle() const {return 0;};
    virtual bool SetAngle(float ang) {return false;};

    virtual void SetWidth(float newWidth) {};
    virtual void SetHeight(float newHeight) {};

    virtual void OnPositionChanged();

    #if defined(GD_IDE_ONLY)
    virtual void GetPropertyForDebugger (unsigned int propertyNb, std::string & name, std::string & value) const;
    virtual bool ChangeProperty(unsigned int propertyNb, std::string newValue);
    virtual unsigned int GetNumberOfProperties() const;
    #endif

    virtual std::vector<Polygon2d> GetHitBoxes() const;

    bool IsCollidingWithTile(int tileLayer, int tileCol, int tileRow, std::map<std::string, std::vector<RuntimeObject*>*> objectsLists, bool isInverted);

    TileSetProxy tileSet;
    TileMapProxy tileMap;

private:

    sf::VertexArray vertexArray;
    std::vector<Polygon2d> hitboxes;

    boost::shared_ptr<SFMLTextureWrapper> texture;

    float oldX;
    float oldY;
};

void DestroyTileMapObject(gd::Object * object);
gd::Object * CreateTileMapObject(std::string name);

void DestroyRuntimeTileMapObject(RuntimeObject * object);
RuntimeObject * CreateRuntimeTileMapObject(RuntimeScene & scene, const gd::Object & object);
#endif // TILEDSPRITEOBJECT_H