#include "sqltextedit.h"
#include "PreferencesDialog.h"
#include "SqlUiLexer.h"

#include <QFile>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QTextBlock>
#include <QUrl>
#include <QMimeData>
#include <cmath>

SqlTextEdit::SqlTextEdit(QWidget* parent) :
    QsciScintilla(parent)
{
    // Set font
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    font.setPointSize(PreferencesDialog::getSettingsValue("editor", "fontsize").toInt());
    setFont(font);

    // Show line numbers
    QFont marginsfont(QFont("Monospace"));
    marginsfont.setPointSize(font.pointSize());
    setMarginsFont(marginsfont);
    setMarginLineNumbers(0, true);
    setMarginsBackgroundColor(Qt::lightGray);
    connect(this, SIGNAL(linesChanged()), this, SLOT(updateLineNumberAreaWidth()));
    updateLineNumberAreaWidth();

    // Highlight current line
    setCaretLineVisible(true);
    setCaretLineBackgroundColor(QColor(PreferencesDialog::getSettingsValue("syntaxhighlighter", "currentline_colour").toString()));

    // Enable auto completion
    setAutoCompletionThreshold(1);
    setAutoCompletionCaseSensitivity(false);
    setAutoCompletionShowSingle(true);
    setAutoCompletionSource(QsciScintilla::AcsAll);

    // Set icons for auto completion
    registerImage(SqlUiLexer::ApiCompleterIconIdKeyword, QImage(":/icons/api_keyword"));
    registerImage(SqlUiLexer::ApiCompleterIconIdFunction, QImage(":/icons/api_function"));
    registerImage(SqlUiLexer::ApiCompleterIconIdTable, QImage(":/icons/api_table"));

    // Enable brace matching
    setBraceMatching(QsciScintilla::SloppyBraceMatch);

    // Enable auto indentation
    setAutoIndent(true);

    // Set tab width
    setTabWidth(PreferencesDialog::getSettingsValue("editor", "tabsize").toInt());
}

SqlTextEdit::~SqlTextEdit()
{
}

void SqlTextEdit::updateLineNumberAreaWidth()
{
    // Cancel now if no lexer has been set so far
    if(lexer() == 0)
        return;

    // Calculate number of digits of the current number of lines
    int digits = std::floor(std::log10(lines())) + 1;

    // Calculate the width of this number if it was all zeros (this is because a 1 might require less space than a 0 and this could
    // cause some flickering depending on the font) and set the new margin width.
    QFont font = lexer()->defaultFont(QsciLexerSQL::Default);
    setMarginWidth(0, QFontMetrics(font).width(QString("0").repeated(digits)) + 5);
}

void SqlTextEdit::setLexer(QsciLexer* lexer)
{
    // Call the parent implementation
    QsciScintilla::setLexer(lexer);

    // This is called in the constructor of the editor but as the lexer isn't set at that time it doesn't do anything
    updateLineNumberAreaWidth();
}

void SqlTextEdit::dropEvent(QDropEvent* e)
{
    QList<QUrl> urls = e->mimeData()->urls();
    if(urls.isEmpty())
        return QsciScintilla::dropEvent(e);

    QString file = urls.first().toLocalFile();
    if(!QFile::exists(file))
        return;

    QFile f(file);
    f.open(QIODevice::ReadOnly);
    setText(f.readAll());
    f.close();
}
