/**

GDevelop - Path Behavior Extension
Copyright (c) 2010-2016 Florian Rival (Florian.Rival@gmail.com)
This project is released under the MIT License.
*/

#ifndef RUNTIMESCENEPATHDATAS_H
#define RUNTIMESCENEPATHDATAS_H
#include <SFML/System/Vector2.hpp>
#include <map>
#include <vector>
#include "GDCpp/Runtime/BehaviorsRuntimeSharedData.h"
#include "GDCpp/Runtime/String.h"

class ScenePathDatas;
class ContactListener;

/**
 * Datas shared by Path Behavior at runtime
 */
class GD_EXTENSION_API RuntimeScenePathDatas
    : public BehaviorsRuntimeSharedData {
 public:
  RuntimeScenePathDatas(const ScenePathDatas& behaviorSharedDatas);
  virtual ~RuntimeScenePathDatas();
  virtual std::shared_ptr<BehaviorsRuntimeSharedData> Clone() const {
    return std::shared_ptr<BehaviorsRuntimeSharedData>(
        new RuntimeScenePathDatas(*this));
  }

  std::map<gd::String, std::vector<sf::Vector2f> >
      globalPaths;  ///< Map containing all the global paths

 private:
};

#endif  // RUNTIMESCENEPATHDATAS_H
