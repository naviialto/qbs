/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Build Suite.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef TST_BLACKBOX_H
#define TST_BLACKBOX_H

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QProcessEnvironment>
#include <QtTest>

class QbsRunParameters
{
public:
    QbsRunParameters()
    {
        init();
    }

    QbsRunParameters(const QString &cmd, const QStringList &args = QStringList())
        : command(cmd), arguments(args)
    {
        init();
    }

    QbsRunParameters(const QStringList &args)
        : arguments(args)
    {
        init();
    }

    void init()
    {
        expectFailure = false;
        useProfile = true;
        environment = QProcessEnvironment::systemEnvironment();
    }

    QString command;
    QStringList arguments;
    QProcessEnvironment environment;
    bool expectFailure;
    bool useProfile;
};

class TestBlackbox : public QObject
{
    Q_OBJECT
    const QString testDataDir;
    const QString testSourceDir;
    const QString qbsExecutableFilePath;
    const QString defaultInstallRoot;

public:
    TestBlackbox();

protected:
    int runQbs(const QbsRunParameters &params = QbsRunParameters());
    void rmDirR(const QString &dir);
    static QByteArray unifiedLineEndings(const QByteArray &ba);
    static void sanitizeOutput(QByteArray *ba);

public slots:
    void initTestCase();

private slots:
    void buildDirectories();
    void changedFiles_data();
    void changedFiles();
    void dependenciesProperty();
    void dynamicMultiplexRule();
    void dynamicRuleOutputs();
    void erroneousFiles_data();
    void erroneousFiles();
    void fileDependencies();
    void jsExtensionsFile();
    void jsExtensionsFileInfo();
    void jsExtensionsProcess();
    void jsExtensionsPropertyList();
    void jsExtensionsTextFile();
    void nonBrokenFilesInBrokenProduct();
    void qmlDebugging();
    void properQuoting();
    void radAfterIncompleteBuild_data();
    void radAfterIncompleteBuild();
    void usingsAsSoleInputsNonMultiplexed();
    void clean();
    void renameDependency();
    void track_qrc();
    void track_qobject_change();
    void trackAddFile();
    void trackExternalProductChanges();
    void trackRemoveFile();
    void trackAddFileTag();
    void trackRemoveFileTag();
    void trackAddMocInclude();
    void trackAddProduct();
    void trackRemoveProduct();
    void wildcardRenaming();
    void recursiveRenaming();
    void recursiveWildcards();
    void ruleConditions();
    void ruleCycle();
    void overrideProjectProperties();
    void productProperties();
    void propertyChanges();
    void installedApp();
    void toolLookup();
    void checkProjectFilePath();
    void missingProfile();
    void testAssembly();
    void testNsis();
    void testEmbedInfoPlist();
    void testWiX();
    void testNodeJs();
    void testTypeScript();
    void testIconset();
    void testIconsetApp();
    void testAssetCatalog();

private:
    QByteArray m_qbsStderr;
    QByteArray m_qbsStdout;
};

#endif // TST_BLACKBOX_H
