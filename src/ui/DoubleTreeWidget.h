//
//          Copyright (c) 2020
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Martin Marmsoler
//

#ifndef DOUBLETREEWIDGET_H
#define DOUBLETREEWIDGET_H

#include "DetailView.h" // ContentWidget

class TreeModel;
class TreeView;
class BlameEditor;
class StatePushButton;
class DiffView;

// button in treeview: https://stackoverflow.com/questions/40716138/how-to-add-a-button-to-a-qtreeview-row

/*!
 * \brief The DoubleTreeWidget class
 * TreeView like in GitKraken
 */
class DoubleTreeWidget : public ContentWidget
{
  Q_OBJECT
  
public:
  DoubleTreeWidget(const git::Repository &repo, QWidget *parent = nullptr);
  QString selectedFile() const override;

  void setDiff(
    const git::Diff &diff,
    const QString &file = QString(),
    const QString &pathspec = QString()) override;


protected:

private:
  enum View {
      Blame,
      Diff,
  };

  void selectFile(const QString& file);
  void fileSelected(const QModelIndex &index);
  void loadEditorContent(const QModelIndex &index);
  void toggleCollapseStagedFiles();
  void toggleCollapseUnstagedFiles();

  TreeModel* mTreeModel{nullptr};
  TreeView* stagedFiles{nullptr};
  TreeView* unstagedFiles{nullptr};
  StatePushButton* collapseButtonStagedFiles{nullptr};
  StatePushButton* collapseButtonUnstagedFiles{nullptr};
  /*!
   * Shows file content
   */
  BlameEditor *mEditor{nullptr};
  /*!
   * Shows the diff of a file
   */
  DiffView* mDiffView{nullptr};

  /*!
   * Shows BlameEditor or DiffView
   */
  QStackedWidget* mFileView{nullptr};
};
#endif // DOUBLETREEWIDGET_H