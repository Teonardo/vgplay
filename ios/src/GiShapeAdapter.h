//! \file GiShapeAdapter.h
//! \brief 定义输出 UIBezierPath 的画布适配器类 GiShapeAdapter
// Copyright (c) 2013-2016 Zhang Yungui, https://github.com/rhcad/vgplay (GPL v3 licensed)

#import <UIKit/UIKit.h>
#import "GiCanvasAdapter.h"

//! GiShapeAdapter输出路径的回调接口
struct GiShapeAdapterCallback
{
    virtual void addPath(UIBezierPath *path, UIColor *strokeColor, UIColor *fillColor) = 0;
    virtual bool beginShape(int type, int sid, CGRect frame) = 0;
    virtual void endShape(int type, int sid) = 0;
};

//! GiShapeAdapterCallback 的默认实现
class GiShapeCallback : public GiShapeAdapterCallback
{
public:
    GiShapeCallback(CALayer *rootLayer, bool hidden);
    CALayer *layer();
    
private:
    virtual void addPath(UIBezierPath *path, UIColor *strokeColor, UIColor *fillColor);
    virtual bool beginShape(int type, int sid, CGRect frame);
    virtual void endShape(int type, int sid);
    
    CALayer *_rootLayer;
    CALayer *_shapeLayer;
    bool    _hidden;
};

//! 输出 UIBezierPath 的画布适配器类
/*! \ingroup GROUP_IOS
 */
class GiShapeAdapter : public GiCanvas
{
public:
    GiShapeAdapter(GiShapeAdapterCallback* shapeCallback);
    void endOutput();
    
public:
    void setPen(int argb, float width, int style, float phase, float orgw);
    void setBrush(int argb, int style);
    void clearRect(float x, float y, float w, float h);
    void drawRect(float x, float y, float w, float h, bool stroke, bool fill);
    void drawLine(float x1, float y1, float x2, float y2);
    void drawEllipse(float x, float y, float w, float h, bool stroke, bool fill);
    void beginPath();
    void moveTo(float x, float y);
    void lineTo(float x, float y);
    void bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y);
    void quadTo(float cpx, float cpy, float x, float y);
    void closePath();
    void drawPath(bool stroke, bool fill);
    void saveClip();
    void restoreClip();
    bool clipRect(float x, float y, float w, float h);
    bool clipPath();
    bool drawHandle(float x, float y, int type, float angle);
    bool drawBitmap(const char* name, float xc, float yc, float w, float h, float angle);
    float drawTextAt(const char* text, float x, float y, float h, int align, float angle);
    bool beginShape(int type, int sid, int version, float x, float y, float w, float h);
    void endShape(int type, int sid, float x, float y);
    
private:
    bool hasLineColor() const;
    bool hasFillColor() const;
    void fireLastPath();
    void checkNeedFire(bool stroke, bool fill);
    
private:
    GiShapeAdapterCallback* _callback;
    UIBezierPath    *_container;
    UIBezierPath    *_path;
    UIColor         *_lineColor;
    UIColor         *_fillColor;
};
