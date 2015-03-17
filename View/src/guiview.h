#ifndef GUIVIEW_H_
#define GUIVIEW_H_

#include <QComboBox>
#include <QPushbutton>
#include <QGraphicsScene>




/**
 * This child class of view uses the mouse and a graphic
 * user interface to pass user information to controller
 */


class GuiView: public View
{
	Q_OBJECT

public: GuiView();


/**
 * The combo box holds actions. When the user selects an action and
 * confirms it via the accompanying confirmation button the
 * signal activates a slot that sends the text id of the view
 * and the requested action to controller. As long as the button
 * is held down the action will be continuously carried out.
 */

		QComboBox actionBox;
		QGraphicsScene scene;
		QPushButton actionButton;
		QPushButton closeButton;



/*		Actions
 * 		void moveForward(QMouseEvent *mousemot);
		void moveBackward(QMouseEvent *mousemot);
		void moveLeft(QMouseEvent *mousemot);
		void moveRight(QMouseEvent *mousemot);
		void moveUp(QMouseEvent *mousemot);
		void moveDown(QMouseEvent *mousemot);
		void surface(QMouseEvent *mousemot);
		void launchTor(QMouseEvent *mousemot);
		void launchGra(QMouseEvent *mousemot);
*/
		virtual ~GuiView();
}
#endif /* GUIVIEW_H_ */
