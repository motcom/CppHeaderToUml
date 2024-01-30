#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "imagedatainfo.h"
#include "imagelistmanager.h"
#include "imagerender.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class MainWidget : public QWidget {
  Q_OBJECT

public:
  MainWidget(QWidget *parent = nullptr);
  ~MainWidget();

protected:
  void keyPressEvent(QKeyEvent *) override;
  void paintEvent(QPaintEvent *) override;
  void resizeEvent(QResizeEvent *) override;

private:
  // イメージリストの管理オブジェクト
  ImageListManager *im_man;
  ImageRender *image_render;
  ImageDataInfo *im_data_info;

  // widget command-------------
  void hide_tab();
  void always_on_top();

  // utility
  void sizable_permission();

  // inner data
  enum class Mode { normal, zoom };
  Mode cur_mode;
  QSize old_win_size;
  char rotate_flag; // 画像回転(0->1->2->3->0)

  // const
  const float ZOOM_IN_INT = 1.2;
  const float ZOOM_OUT_INT = 0.8;
  const float ZOOM_INIT_INT = 1.0;
  const float MOVE_INT = 100;
};
#endif // MAINWIDGET_H
