#ifndef SQLTEXTEDIT_H
#define SQLTEXTEDIT_H

#include "Qsci/qsciscintilla.h"

class SqlUiLexer;
class QsciLexer;

/**
 * @brief The SqlTextEdit class
 * With basic table and fieldname auto completion.
 * This class is based on the Qt custom completion example.
 */
class SqlTextEdit : public QsciScintilla
{
    Q_OBJECT

public:
    explicit SqlTextEdit(QWidget *parent = 0);
    virtual ~SqlTextEdit();

    virtual void setLexer(QsciLexer* lexer);

protected:
    void dropEvent(QDropEvent* e);

private slots:
    void updateLineNumberAreaWidth();

private:
    SqlUiLexer* m_sqlLexer;
};

#endif
