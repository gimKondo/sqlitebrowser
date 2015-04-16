#ifndef SQLUILEXER_H
#define SQLUILEXER_H

#include "Qsci/qscilexersql.h"

class QsciAPIs;

class SqlUiLexer : public QsciLexerSQL
{
    Q_OBJECT

public:
    explicit SqlUiLexer(QObject *parent = 0);

    enum ApiCompleterIconId
    {
        ApiCompleterIconIdKeyword = 1,
        ApiCompleterIconIdFunction,
        ApiCompleterIconIdTable,
    };

    void setTableNames(QStringList tables);

    const char* keywords(int set) const;

private:
    QsciAPIs* autocompleteApi;

    void setupAutoCompletion();

    QStringList listTables;
    QStringList listFunctions;
};

#endif
