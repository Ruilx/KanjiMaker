#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
public:
	explicit GraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
protected:
	void resizeEvent(QResizeEvent *event);
};

#endif // GRAPHICSVIEW_H
