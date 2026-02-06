# GitHub Project Board Setup Guide

This guide provides instructions for creating and configuring a GitHub Project board to track technique additions, issues, and contributions.

## Why Use Project Boards?

Project boards help you:
- **Track new techniques**: Plan and organize technique additions
- **Manage contributions**: See what's in progress, what's done
- **Visualize workflow**: Kanban-style view of project status
- **Prioritize work**: Focus on high-value tasks
- **Coordinate contributors**: See who's working on what

## Option 1: GitHub Projects (New Beta)

GitHub's new Projects feature offers more flexibility.

### Creating a New Project

1. **Navigate to your repository**
   - Go to `https://github.com/yourusername/anti`

2. **Open Projects tab**
   - Click "Projects" in the top menu
   - If you don't see it, enable it in Settings → Features → Projects

3. **Create new project**
   - Click "New project" or "Create a project"
   - Choose "Board" or "Table" view
   - Name it: **"Anti-Analysis Techniques Roadmap"**

4. **Configure project**
   - Description: "Track technique additions, documentation improvements, and contributions"
   - Set visibility: Public (so contributors can see it)
   - Select template: "Board" (recommended)

### Recommended Board Layout

Create these columns/statuses:

#### Column 1: 📋 Backlog
**Purpose**: Techniques and features planned but not started

**Items to add**:
- New technique ideas
- Feature requests from issues
- Documentation improvements
- Research tasks

**Example cards**:
- "Add technique 040: Stack cookie check"
- "Add technique 041: Timing-based detection"
- "Research anti-VM techniques"

#### Column 2: 📝 Planned
**Purpose**: Approved and prioritized for implementation

**Criteria for moving here**:
- Technique is well-defined
- Research is complete
- Ready to be assigned

**Example cards**:
- "Implement technique 040 with test cases"
- "Create Phase 3 documentation"

#### Column 3: 🚧 In Progress
**Purpose**: Currently being worked on

**Move cards here when**:
- Someone is actively working on it
- PR is being drafted
- Implementation has started

**Example cards**:
- "PR #15: Add technique 040"
- "Updating README for Phase 2"

#### Column 4: 👀 Review
**Purpose**: Awaiting review or testing

**Move cards here when**:
- PR is submitted
- Code is complete but needs testing
- Documentation needs review

**Example cards**:
- "PR #15: Review technique 040 implementation"
- "Test technique on multiple debuggers"

#### Column 5: ✅ Done
**Purpose**: Completed and merged

**Archive after**:
- 1-2 weeks for visibility
- Major milestone completed

**Example cards**:
- "Technique 040 merged and documented"
- "Phase 2 complete"

### Automation Rules

Configure automatic card movement:

1. **Issues → Backlog**
   - Auto-add new issues to Backlog
   - Label with "technique-request" or "enhancement"

2. **PRs → In Progress**
   - Auto-add PRs to "In Progress" when opened
   - Move to "Review" when marked ready for review

3. **PRs → Done**
   - Auto-move to "Done" when PR is merged
   - Auto-close linked issues

### Setting Up Automation

1. Click project "..." menu → Settings
2. Go to "Workflows" tab
3. Enable workflows:
   - ✓ "Item added to project" → Set status to Backlog
   - ✓ "Pull request merged" → Set status to Done
   - ✓ "Issue closed" → Set status to Done

## Option 2: Classic Project Boards

Simpler but less flexible than new Projects.

### Creating Classic Board

1. **Go to Projects tab**
2. **Click "New project"**
3. **Choose "Classic project"**
4. **Configure**:
   - Name: "Technique Development"
   - Description: "Track anti-analysis technique development"
   - Template: "Automated kanban"

### Classic Board Columns

The automated kanban template creates:
- **To Do**: New issues/cards
- **In Progress**: Being worked on
- **Done**: Completed

You can customize by adding:
- **Needs Review**: PRs awaiting review
- **Testing**: Techniques being tested
- **Blocked**: Waiting on something

### Adding Cards

**Method 1: From Issues**
1. Go to Issues tab
2. Create new issue
3. On the right sidebar → Projects → Select your project
4. Issue automatically appears on board

**Method 2: Quick Notes**
1. Open project board
2. Click "+ Add cards"
3. Type note and press Enter
4. Convert to issue later if needed

## Recommended Card Labels

Apply these labels to organize cards:

### Priority Labels:
- 🔴 **P0 - Critical**: Blocking issues
- 🟠 **P1 - High**: Important, not blocking
- 🟡 **P2 - Medium**: Normal priority
- 🟢 **P3 - Low**: Nice to have

### Type Labels:
- 🆕 **new-technique**: Adding a new technique
- 📚 **documentation**: Doc improvements
- 🐛 **bug**: Bug fixes
- ✨ **enhancement**: Feature improvements
- 🧪 **testing**: Testing tasks

### Category Labels:
- 🛡️ **anti-debugger**: Debugger detection techniques
- 🔍 **anti-sandbox**: Sandbox detection techniques
- 🔒 **anti-reversing**: Reversing prevention techniques

### Status Labels:
- 🚧 **wip**: Work in progress
- 👀 **needs-review**: Awaiting review
- ⏸️ **blocked**: Blocked on something
- ❓ **question**: Needs discussion

## Populating Initial Cards

### Technique Ideas (Backlog)

Add these as "To Do" cards:

**Anti-Debugger Ideas**:
- [ ] Stack cookie detection
- [ ] TLS callbacks anti-debug
- [ ] Parent process check (explorer.exe)
- [ ] SeDebugPrivilege check
- [ ] Kernel debugger detection (KUSER_SHARED_DATA)

**Anti-Sandbox Ideas**:
- [ ] Mouse/keyboard activity check
- [ ] CPU count check
- [ ] Memory size check
- [ ] File existence check (malware artifacts)
- [ ] Network activity simulation

**Documentation Tasks**:
- [ ] Standardize all technique READMEs
- [ ] Add effectiveness ratings
- [ ] Create bypass documentation
- [ ] Add GIF demonstrations
- [ ] Create comparison matrix

**Infrastructure Tasks**:
- [ ] Improve CI/CD for mixed builds
- [ ] Add automated testing
- [ ] Create release workflow
- [ ] Set up GitHub Pages

## Using Project Views

### Board View (Default)
- Visual Kanban board
- Drag-and-drop cards between columns
- Quick overview of status

### Table View
- Spreadsheet-like layout
- Sort by priority, assignee, labels
- Bulk editing
- Export data

### Roadmap View
- Timeline visualization
- Set start/end dates
- Milestone tracking
- Gantt-style view

### Creating Custom Views

1. Click "New view"
2. Choose type (Board/Table/Roadmap)
3. Configure filters:
   - By label (e.g., only "new-technique")
   - By assignee
   - By milestone
   - By status

**Example custom views**:
- **"My Work"**: Assigned to me, status: In Progress
- **"Documentation"**: Label: documentation
- **"High Priority"**: Priority: P0 or P1
- **"Anti-Debugger"**: Label: anti-debugger

## Milestones

Create milestones to group related work:

### Milestone Examples:

**"Phase 2 Complete"**
- Due: 2026-03-15
- Description: Complete all Phase 2 tasks
- Issues:
  - Visual diagrams ✅
  - Enhanced READMEs
  - GitHub Pages setup
  - Release creation

**"50 Techniques"**
- Due: 2026-06-30
- Description: Reach 50 total techniques
- Issues:
  - Add techniques 040-050
  - Document each technique
  - Test all techniques

**"v1.0 Release"**
- Due: 2026-04-30
- Description: First official release
- Issues:
  - All techniques documented
  - CI/CD working
  - Binaries compiled
  - Release notes written

## Best Practices

### 1. Keep It Updated
- Move cards as work progresses
- Close completed cards
- Archive old cards periodically

### 2. Use Descriptive Titles
- ❌ "Fix bug"
- ✅ "Fix: Technique 012 crashes on Windows 11"

### 3. Add Context
- Link related issues
- Add references
- Include acceptance criteria

### 4. Assign Owners
- Assign cards to contributors
- One person per card (primary owner)
- Tag additional reviewers

### 5. Set Realistic Estimates
- Use story points or time estimates
- Don't overcommit
- Adjust as needed

### 6. Review Regularly
- Weekly review of In Progress
- Monthly review of Backlog
- Quarterly planning session

## Integration with Issues and PRs

### Linking Issues to Cards

In issue description or PR:
```markdown
Closes #15
Fixes #23
Related to #40
```

This automatically:
- Links issue to card
- Moves card on PR merge
- Closes linked issues

### Using Keywords

In commit messages:
```bash
git commit -m "feat: add technique 040

Closes #50"
```

This closes issue #50 and updates project board.

## Example Workflow

### Adding a New Technique

1. **Create Issue**
   ```
   Title: Add technique 040: Stack Cookie Check
   Labels: new-technique, anti-debugger, P1
   Milestone: 50 Techniques
   ```

2. **Card Moves to Backlog** (automatic)

3. **Planning**
   - Research technique
   - Add implementation notes
   - Move to "Planned" when ready

4. **Implementation**
   - Assign to yourself
   - Move to "In Progress"
   - Create branch: `git checkout -b technique/040-stack-cookie`

5. **Submit PR**
   - PR auto-added to "In Progress"
   - Request review
   - Move to "Review" when ready

6. **Merge**
   - After approval, merge PR
   - Card auto-moves to "Done"
   - Issue auto-closes

## Quick Start Checklist

- [ ] Create new project board
- [ ] Set up columns (Backlog, Planned, In Progress, Review, Done)
- [ ] Configure automation rules
- [ ] Add labels (priority, type, category)
- [ ] Create initial milestones
- [ ] Add technique ideas to Backlog
- [ ] Link existing issues to project
- [ ] Create custom views for filtering
- [ ] Document workflow for contributors
- [ ] Share project board link in README

## Adding Project Board to README

Add this to your README.md:

```markdown
## Project Board

Track project progress, new techniques, and contributions on our [Project Board](https://github.com/USERNAME/anti/projects/1).

### Quick Links:
- 📋 [View all techniques](https://github.com/USERNAME/anti/projects/1?view=board)
- 🆕 [Planned techniques](https://github.com/USERNAME/anti/projects/1?filterQuery=status%3A%22Planned%22)
- 🚧 [In progress](https://github.com/USERNAME/anti/projects/1?filterQuery=status%3A%22In+Progress%22)
```

## Resources

- [GitHub Projects Documentation](https://docs.github.com/en/issues/planning-and-tracking-with-projects)
- [Project Board Templates](https://docs.github.com/en/issues/planning-and-tracking-with-projects/learning-about-projects/quickstart-for-projects)
- [Automation Guide](https://docs.github.com/en/issues/planning-and-tracking-with-projects/automating-your-project)

---

**Last Updated**: 2026-02-06
**Recommended**: Use new GitHub Projects (Beta) for best features
**Setup Time**: ~15 minutes
