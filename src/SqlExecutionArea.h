#ifndef SQLEXECUTIONAREA_H
#define SQLEXECUTIONAREA_H

#include "sqltextedit.h"

#include <QWidget>

class QsciScintilla;
class SqlUiLexer;
class SqliteTableModel;
class DBBrowserDB;
class QMenu;
class QTextEdit;

namespace Ui {
class SqlExecutionArea;
}

class SqlExecutionArea : public QWidget
{
    Q_OBJECT

public:
    explicit SqlExecutionArea(QWidget* parent, DBBrowserDB* _db, SqlUiLexer* lexer);
    ~SqlExecutionArea();

    QString getSql() const;
    QString getSelectedSql() const;

    QString fileName() const { return sqlFileName; }
    void setFileName(const QString& filename) { sqlFileName = filename; }

    SqliteTableModel* getModel() { return model; }
    QTextEdit* getResultView();
    QsciScintilla* getEditor();

public slots:
    virtual void finishExecution(const QString& result);
    virtual void enableSaveButton(bool enable);
    virtual void saveAsCsv();
    virtual void saveAsView();

private:
    DBBrowserDB* db;
    SqliteTableModel* model;
    QMenu* menuPopupSave;
    QString sqlFileName;
    Ui::SqlExecutionArea* ui;
};

#endif
