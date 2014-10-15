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
** conditions see http://www.qt.io/licensing.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "nodeset.h"

#include "artifact.h"
#include "rulenode.h"
#include <language/language.h>  // because of RulePtr
#include <tools/persistence.h>
#include <tools/qbsassert.h>

namespace qbs {
namespace Internal {

NodeSet::NodeSet()
{
}

NodeSet::NodeSet(const NodeSet &other)
    : m_data(other.m_data)
{
}

NodeSet &NodeSet::unite(const NodeSet &other)
{
    m_data.insert(other.begin(), other.end());
    return *this;
}

void NodeSet::remove(BuildGraphNode *node)
{
    m_data.erase(node);
}

void NodeSet::load(PersistentPool &pool)
{
    clear();
    int i;
    pool.stream() >> i;
    for (; --i >= 0;) {
        int t;
        pool.stream() >> t;
        BuildGraphNode *node = 0;
        switch (static_cast<BuildGraphNode::Type>(t)) {
        case BuildGraphNode::ArtifactNodeType:
            node = pool.idLoad<Artifact>();
            break;
        case BuildGraphNode::RuleNodeType:
            node = pool.idLoad<RuleNode>();
            break;
        }
        QBS_CHECK(node);
        insert(node);
    }
}

void NodeSet::store(PersistentPool &pool) const
{
    pool.stream() << count();
    for (NodeSet::const_iterator it = constBegin(); it != constEnd(); ++it) {
        pool.stream() << int((*it)->type());
        pool.store(*it);
    }
}

} // namespace Internal
} // namespace qbs
