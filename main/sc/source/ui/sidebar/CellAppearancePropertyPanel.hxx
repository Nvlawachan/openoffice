/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/

#ifndef SC_PROPERTYPANEL_APPEARANCE_HXX
#define SC_PROPERTYPANEL_APPEARANCE_HXX

#include <sfx2/sidebar/ControllerItem.hxx>
#include <sfx2/sidebar/IContextChangeReceiver.hxx>
#include <boost/scoped_ptr.hpp>
#include <svx/sidebar/ColorPopup.hxx>

class FixedText;
namespace svx { class ToolboxButtonColorUpdater; }
namespace sc { namespace sidebar { 
    class CellLineStylePopup;
    class CellBorderStylePopup;
    class CellLineStyleControl;
    class CellBorderUpdater; 
}}
class ToolBox;
class CheckBox;

namespace sc { namespace sidebar {

class CellAppearancePropertyPanel
:   public Control,
    public ::sfx2::sidebar::IContextChangeReceiver,
    public ::sfx2::sidebar::ControllerItem::ItemUpdateReceiverInterface
{
private:
    friend class CellLineStyleControl;
    friend class CellBorderStyleControl;

public:
    static CellAppearancePropertyPanel* Create(
        Window* pParent,
        const cssu::Reference<css::frame::XFrame>& rxFrame,
        SfxBindings* pBindings);

    virtual void DataChanged(
        const DataChangedEvent& rEvent);

    virtual void HandleContextChange(
        const ::sfx2::sidebar::EnumContext aContext);

    virtual void NotifyItemUpdate(
        const sal_uInt16 nSId,
        const SfxItemState eState,
        const SfxPoolItem* pState,
        const bool bIsEnabled);

    SfxBindings* GetBindings();

    virtual void Resize (void);

private:
    //ui controls
    ::boost::scoped_ptr< FixedText >        mpFTFillColor;
    ::boost::scoped_ptr< Window >           mpTBFillColorBackground;
    ::boost::scoped_ptr< ToolBox >          mpTBFillColor;
    ::boost::scoped_ptr< ::svx::ToolboxButtonColorUpdater > mpFillColorUpdater;

    ::boost::scoped_ptr< FixedText >        mpFTCellBorder;
    ::boost::scoped_ptr< Window >           mpTBCellBorderBackground;
    ::boost::scoped_ptr< ToolBox >          mpTBCellBorder;
    ::boost::scoped_ptr< CellBorderUpdater > mpCellBorderUpdater;

    ::boost::scoped_ptr< Window >           mpTBLineStyleBackground;
    ::boost::scoped_ptr< ToolBox >          mpTBLineStyle;

    ::boost::scoped_ptr< Window >           mpTBLineColorBackground;
    ::boost::scoped_ptr< ToolBox >          mpTBLineColor;
    ::boost::scoped_ptr< ::svx::ToolboxButtonColorUpdater > mpLineColorUpdater;

    ::boost::scoped_ptr< CheckBox >         mpCBXShowGrid;

    ::sfx2::sidebar::ControllerItem         maBackColorControl;
    ::sfx2::sidebar::ControllerItem         maLineColorControl;
    ::sfx2::sidebar::ControllerItem         maLineStyleControl;
    ::sfx2::sidebar::ControllerItem         maBorderOuterControl;
    ::sfx2::sidebar::ControllerItem         maBorderInnerControl;
    ::sfx2::sidebar::ControllerItem         maGridShowControl;
    ::sfx2::sidebar::ControllerItem         maBorderTLBRControl;
    ::sfx2::sidebar::ControllerItem         maBorderBLTRControl;

    // images
    Image                                   maIMGBKColor;
    Image                                   maIMGCellBorder;
    Image                                   maIMGLineColor;
    Image                                   maIMGLineStyle1;
    Image                                   maIMGLineStyle2;
    Image                                   maIMGLineStyle3;
    Image                                   maIMGLineStyle4;
    Image                                   maIMGLineStyle5;
    Image                                   maIMGLineStyle6;
    Image                                   maIMGLineStyle7;
    Image                                   maIMGLineStyle8;
    Image                                   maIMGLineStyle9;

    // high contrast images
    Image                                   maIMGBKColorH;
    Image                                   maIMGLineStyle0H;
    Image                                   maIMGLineStyle1H;
    Image                                   maIMGLineStyle2H;
    Image                                   maIMGLineStyle3H;
    Image                                   maIMGLineStyle4H;
    Image                                   maIMGLineStyle5H;
    Image                                   maIMGLineStyle6H;
    Image                                   maIMGLineStyle7H;
    Image                                   maIMGLineStyle8H;
    Image                                   maIMGLineStyle9H;

    // cell background color
    Color                                   maBackColor;

    // cell line color(s)
    Color                                   maLineColor;
    Color                                   maTLBRColor;
    Color                                   maBLTRColor;

    // BorderStyle defines
    sal_uInt16                              mnIn;
    sal_uInt16                              mnOut;
    sal_uInt16                              mnDis;
    sal_uInt16                              mnTLBRIn;
    sal_uInt16                              mnTLBROut;
    sal_uInt16                              mnTLBRDis;
    sal_uInt16                              mnBLTRIn;
    sal_uInt16                              mnBLTROut;
    sal_uInt16                              mnBLTRDis;

    /// bitfield
    bool                                    mbBackColorAvailable : 1;
    bool                                    mbLineColorAvailable : 1;
    bool                                    mbBorderStyleAvailable : 1;

    // CellBorder defines
    bool                                    mbLeft : 1;
    bool                                    mbRight : 1;
    bool                                    mbTop : 1;
    bool                                    mbBottom : 1;
    bool                                    mbVer : 1;
    bool                                    mbHor : 1;

    bool                                    mbOuterBorder : 1; // mbLeft || mbRight || mbTop || mbBottom
    bool                                    mbInnerBorder : 1; // mbVer || mbHor || bLeft || bRight || bTop || bBottom

    bool                                    mbTLBR : 1;
    bool                                    mbBLTR : 1;

    // popups
    svx::sidebar::ColorPopup                maFillColorPopup; 
    svx::sidebar::ColorPopup                maLineColorPopup; 
    ::boost::scoped_ptr< CellLineStylePopup > mpCellLineStylePopup;
    ::boost::scoped_ptr< CellBorderStylePopup > mpCellBorderStylePopup;

    cssu::Reference<css::frame::XFrame>     mxFrame;
    ::sfx2::sidebar::EnumContext            maContext;
    SfxBindings*                            mpBindings;

    DECL_LINK(TbxBKColorSelectHdl, ToolBox*);
    DECL_LINK(TbxLineColorSelectHdl, ToolBox*);
    DECL_LINK(TbxCellBorderSelectHdl, ToolBox*);
    DECL_LINK(TbxLineStyleSelectHdl, ToolBox*);
    DECL_LINK(CBOXGridShowClkHdl, void*);

    // for fill color picker 
    svx::sidebar::PopupControl* CreateFillColorPopupControl(svx::sidebar::PopupContainer* pParent);
    void SetFillColor(const String& rsColorName, const Color aColor);

    // for line color picker 
    svx::sidebar::PopupControl* CreateLineColorPopupControl(svx::sidebar::PopupContainer* pParent);
    void SetLineColor(const String& rsColorName, const Color aColor);

    // for CellLineStyle popup
    svx::sidebar::PopupControl* CreateCellLineStylePopupControl(svx::sidebar::PopupContainer* pParent);
    void EndCellLineStylePopupMode(void);

    // for CellBorderStyle popup
    svx::sidebar::PopupControl* CreateCellBorderStylePopupControl(svx::sidebar::PopupContainer* pParent);
    void EndCellBorderStylePopupMode(void);

    // constructor/destuctor
    CellAppearancePropertyPanel(
        Window* pParent,
        const cssu::Reference<css::frame::XFrame>& rxFrame,
        SfxBindings* pBindings);
    virtual ~CellAppearancePropertyPanel();

    void Initialize();
    void SetStyleIcon();
    void UpdateControlState();
};

} } // end of namespace ::sc::sidebar

#endif
// eof
