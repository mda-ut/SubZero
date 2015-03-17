/*
 * view.h
 *
 *  Created on: Feb 15, 2015
 *      Author: edem
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "observer.h"
#include <QWidget>
#include <QGridLayout>
#include <QPixMap>
#include <QGraphicsScene>
#include <QEvent>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QColor>

/** This abstract class inherits observer's
 * functionality and displays the data via use of
 * the Qt framework: The cv::Mat type holding image
 * data is used to develop the QPixMap which is then
 * turned into an image and displayed on the graphics
 * scene
 */

class View : public Observer
{
	Q_OBJECT

public:
		View();

		/**
		 * @param type Hold the string that is sent to
		 * controller to identify a view
		 */
		char[5] type;
		QWidget viewWindow;
		QPixMap pixMat;
		QGridLayout viewLayout;

		/**
		 * The QPaintEvent is used to continuously draw the
		 * images received in lieu of a separate display function
		 */
		QPaintEvent painter;
		QPen stencil;
		QBrush brush;
		QColour currentColour;


		virtual ~View();
};


#endif /* VIEW_H_ */
