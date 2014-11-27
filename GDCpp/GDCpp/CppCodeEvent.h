/*
 * GDevelop C++ Platform
 * Copyright 2008-2014 Florian Rival (Florian.Rival@gmail.com). All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#if defined(GD_IDE_ONLY)

#ifndef CPPCODEEVENT_H
#define CPPCODEEVENT_H
#include "GDCore/Events/Event.h"
class RuntimeScene;
namespace gd { class Instruction; }
namespace gd { class MainFrameWrapper; }
namespace gd { class Project; }
namespace gd { class SerializerElement; }
namespace gd { class EventsEditorItemsAreas; }
namespace gd { class EventsEditorSelection; }
namespace gd { class Layout; }
class wxWindow;

/**
 * \brief Builtin internal event that pick an object of a list each time it is repeated
 */
class CppCodeEvent : public gd::BaseEvent
{
public:
    CppCodeEvent();
    CppCodeEvent(const CppCodeEvent & event);
    virtual ~CppCodeEvent() {};

    CppCodeEvent& operator=(const CppCodeEvent & event);
    virtual CppCodeEvent * Clone() const { return new CppCodeEvent(*this);}

    virtual bool IsExecutable() const {return true;}
    virtual bool CanHaveSubEvents() const {return false;}

    void EnsureAssociatedSourceFileIsUpToDate(gd::Project & parentGame) const;

    const std::vector<std::string> & GetIncludeFiles() const { return includeFiles; };
    void SetIncludeFiles(const std::vector<std::string> & include_) { includeFiles = include_; };

    const std::string & GetInlineCode() const { return inlineCode; };
    void SetInlineCode(const std::string & code) { inlineCode = code; };

    const std::string & GetFunctionToCall() const;
    void SetFunctionToCall(const std::string & functionToCall_) { functionToCall = functionToCall_; };

    bool IsFunctionNameAutoGenerated() const { return functionNameAutogenerated; };
    void SetFunctionNameAutoGenerated(bool autogenerate) { functionNameAutogenerated = autogenerate; };

    const std::string & GetAssociatedGDManagedSourceFile(gd::Project & parentGame) const { EnsureAssociatedSourceFileIsUpToDate(parentGame); return associatedGDManagedSourceFile; };

    void SetLastChangeTimeStamp(time_t lastChangeTimeStamp_) { lastChangeTimeStamp = lastChangeTimeStamp_; }

    const std::vector<std::string> & GetDependencies() const { return dependencies; };
    void SetDependencies(const std::vector<std::string> & dependencies_) { dependencies = dependencies_; };

    bool GetPassSceneAsParameter() const { return passSceneAsParameter; };
    void SetPassSceneAsParameter(bool passScene) { passSceneAsParameter = passScene; };

    bool GetPassObjectListAsParameter() const { return passObjectListAsParameter; };
    void SetPassObjectListAsParameter(bool passObjectList) { passObjectListAsParameter = passObjectList; };

    std::string GetObjectToPassAsParameter() const { return objectToPassAsParameter; };
    void SetObjectToPassAsParameter(std::string objectName) { objectToPassAsParameter = objectName; };

    bool IsCodeDisplayedInEditor() const { return codeDisplayedInEditor; };
    void EnableCodeDisplayedInEditor(bool enable) { codeDisplayedInEditor = enable; eventHeightNeedUpdate = true; };

    const std::string & GetDisplayedName() const { return displayedName; };
    void SetDisplayedName(const std::string & displayedName_) { displayedName = displayedName_; };

    virtual void SerializeTo(gd::SerializerElement & element) const;
    virtual void UnserializeFrom(gd::Project & project, const gd::SerializerElement & element);

    /**
     * Called by event editor to draw the event.
     */
    virtual void Render(wxDC & dc, int x, int y, unsigned int width, gd::EventsEditorItemsAreas & areas, gd::EventsEditorSelection & selection, const gd::Platform & platform);

    /**
     * Must return the height of the event when rendered
     */
    virtual unsigned int GetRenderedHeight(unsigned int width, const gd::Platform & platform) const;

    /**
     * Called when the user want to edit the event
     */
    virtual EditEventReturnType EditEvent(wxWindow* parent_, gd::Project & game_, gd::Layout & scene_, gd::MainFrameWrapper & mainFrameWrapper_);

private:
    void Init(const CppCodeEvent & event);
    std::string GenerateAssociatedFileCode() const;
    void AutogenerateFunctionName() const;

    std::vector<std::string> includeFiles;
    std::vector<std::string> dependencies; ///< List of source files that must be compiled and loaded at the same time as the C++ event function.
    mutable std::string functionToCall; ///< The name of the function to call ( Typically located in the include file )
    bool functionNameAutogenerated; ///< If true, the name of the function being called ( and containing the inline code ) will be automatically generated.
    std::string inlineCode; ///< Contains the C++ code of the event, which is inserted into the associated GD-managed source file
    mutable std::string associatedGDManagedSourceFile; ///< "Inline" C++ code is simulated by a call to a function containing the code, function located in a separate source file managed by GD.
    time_t lastChangeTimeStamp; ///< Time of the last change. Used to check if the associated source file must be regenerated.

    bool passSceneAsParameter;
    bool passObjectListAsParameter;
    std::string objectToPassAsParameter;

    bool codeDisplayedInEditor;
    std::string displayedName;

    bool objectsToPickSelected;
};


#endif // CPPCODEEVENT_H

#endif

