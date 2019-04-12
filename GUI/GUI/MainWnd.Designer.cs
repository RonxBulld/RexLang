namespace GUI
{
    partial class MainWnd
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.mainMenuStrip = new System.Windows.Forms.MenuStrip();
            this.文件FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.编辑ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.导航ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.视图ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.调试ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.编译ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.帮助ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mainStatusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.mainSplitContainer = new System.Windows.Forms.SplitContainer();
            this.workSplitContainer = new System.Windows.Forms.SplitContainer();
            this.srcListViewPage = new System.Windows.Forms.TabControl();
            this.srcManager = new System.Windows.Forms.TabPage();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.propertyGrid = new System.Windows.Forms.TabPage();
            this.propertyGrid1 = new System.Windows.Forms.PropertyGrid();
            this.srcTabControl = new System.Windows.Forms.TabControl();
            this.bottomTabPages = new System.Windows.Forms.TabControl();
            this.logPage = new System.Windows.Forms.TabPage();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.重新关联oe文件ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.infoPage = new System.Windows.Forms.TabPage();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.转换为大写ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.转换为小写ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.新建ToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.打开ToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.保存ToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.另存为ToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.新建ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打开ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.另存为ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.最近工程ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关闭ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.剪切ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.复制ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.粘贴ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.剪切ToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.复制ToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.粘贴ToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton8 = new System.Windows.Forms.ToolStripSeparator();
            this.mainMenuStrip.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mainSplitContainer)).BeginInit();
            this.mainSplitContainer.Panel1.SuspendLayout();
            this.mainSplitContainer.Panel2.SuspendLayout();
            this.mainSplitContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.workSplitContainer)).BeginInit();
            this.workSplitContainer.Panel1.SuspendLayout();
            this.workSplitContainer.Panel2.SuspendLayout();
            this.workSplitContainer.SuspendLayout();
            this.srcListViewPage.SuspendLayout();
            this.srcManager.SuspendLayout();
            this.propertyGrid.SuspendLayout();
            this.bottomTabPages.SuspendLayout();
            this.logPage.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainMenuStrip
            // 
            this.mainMenuStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.mainMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件FToolStripMenuItem,
            this.编辑ToolStripMenuItem,
            this.导航ToolStripMenuItem,
            this.视图ToolStripMenuItem,
            this.调试ToolStripMenuItem,
            this.编译ToolStripMenuItem,
            this.帮助ToolStripMenuItem});
            this.mainMenuStrip.Location = new System.Drawing.Point(0, 0);
            this.mainMenuStrip.Name = "mainMenuStrip";
            this.mainMenuStrip.Padding = new System.Windows.Forms.Padding(4, 2, 0, 2);
            this.mainMenuStrip.Size = new System.Drawing.Size(1263, 25);
            this.mainMenuStrip.TabIndex = 0;
            this.mainMenuStrip.Text = "menuStrip1";
            // 
            // 文件FToolStripMenuItem
            // 
            this.文件FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新建ToolStripMenuItem,
            this.打开ToolStripMenuItem,
            this.保存ToolStripMenuItem,
            this.另存为ToolStripMenuItem,
            this.toolStripMenuItem1,
            this.重新关联oe文件ToolStripMenuItem,
            this.toolStripMenuItem2,
            this.最近工程ToolStripMenuItem,
            this.关闭ToolStripMenuItem});
            this.文件FToolStripMenuItem.Name = "文件FToolStripMenuItem";
            this.文件FToolStripMenuItem.Size = new System.Drawing.Size(58, 21);
            this.文件FToolStripMenuItem.Text = "文件(&F)";
            // 
            // 编辑ToolStripMenuItem
            // 
            this.编辑ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.剪切ToolStripMenuItem,
            this.复制ToolStripMenuItem,
            this.粘贴ToolStripMenuItem,
            this.toolStripMenuItem3,
            this.转换为大写ToolStripMenuItem,
            this.转换为小写ToolStripMenuItem});
            this.编辑ToolStripMenuItem.Name = "编辑ToolStripMenuItem";
            this.编辑ToolStripMenuItem.Size = new System.Drawing.Size(59, 21);
            this.编辑ToolStripMenuItem.Text = "编辑(&E)";
            // 
            // 导航ToolStripMenuItem
            // 
            this.导航ToolStripMenuItem.Name = "导航ToolStripMenuItem";
            this.导航ToolStripMenuItem.Size = new System.Drawing.Size(62, 21);
            this.导航ToolStripMenuItem.Text = "导航(&N)";
            // 
            // 视图ToolStripMenuItem
            // 
            this.视图ToolStripMenuItem.Name = "视图ToolStripMenuItem";
            this.视图ToolStripMenuItem.Size = new System.Drawing.Size(60, 21);
            this.视图ToolStripMenuItem.Text = "视图(&V)";
            // 
            // 调试ToolStripMenuItem
            // 
            this.调试ToolStripMenuItem.Name = "调试ToolStripMenuItem";
            this.调试ToolStripMenuItem.Size = new System.Drawing.Size(61, 21);
            this.调试ToolStripMenuItem.Text = "调试(&D)";
            // 
            // 编译ToolStripMenuItem
            // 
            this.编译ToolStripMenuItem.Name = "编译ToolStripMenuItem";
            this.编译ToolStripMenuItem.Size = new System.Drawing.Size(60, 21);
            this.编译ToolStripMenuItem.Text = "编译(&C)";
            // 
            // 帮助ToolStripMenuItem
            // 
            this.帮助ToolStripMenuItem.Name = "帮助ToolStripMenuItem";
            this.帮助ToolStripMenuItem.Size = new System.Drawing.Size(61, 21);
            this.帮助ToolStripMenuItem.Text = "帮助(&H)";
            // 
            // mainStatusStrip
            // 
            this.mainStatusStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.mainStatusStrip.Location = new System.Drawing.Point(0, 634);
            this.mainStatusStrip.Name = "mainStatusStrip";
            this.mainStatusStrip.Padding = new System.Windows.Forms.Padding(1, 0, 10, 0);
            this.mainStatusStrip.Size = new System.Drawing.Size(1263, 22);
            this.mainStatusStrip.TabIndex = 2;
            this.mainStatusStrip.Text = "statusStrip1";
            // 
            // toolStrip1
            // 
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新建ToolStripButton,
            this.打开ToolStripButton,
            this.保存ToolStripButton,
            this.另存为ToolStripButton,
            this.toolStripSeparator1,
            this.剪切ToolStripButton,
            this.复制ToolStripButton,
            this.粘贴ToolStripButton,
            this.toolStripButton8});
            this.toolStrip1.Location = new System.Drawing.Point(0, 25);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1263, 27);
            this.toolStrip1.TabIndex = 3;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // mainSplitContainer
            // 
            this.mainSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainSplitContainer.Location = new System.Drawing.Point(0, 52);
            this.mainSplitContainer.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.mainSplitContainer.Name = "mainSplitContainer";
            this.mainSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // mainSplitContainer.Panel1
            // 
            this.mainSplitContainer.Panel1.Controls.Add(this.workSplitContainer);
            // 
            // mainSplitContainer.Panel2
            // 
            this.mainSplitContainer.Panel2.Controls.Add(this.bottomTabPages);
            this.mainSplitContainer.Size = new System.Drawing.Size(1263, 582);
            this.mainSplitContainer.SplitterDistance = 393;
            this.mainSplitContainer.SplitterWidth = 3;
            this.mainSplitContainer.TabIndex = 4;
            // 
            // workSplitContainer
            // 
            this.workSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.workSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.workSplitContainer.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.workSplitContainer.Name = "workSplitContainer";
            // 
            // workSplitContainer.Panel1
            // 
            this.workSplitContainer.Panel1.Controls.Add(this.srcListViewPage);
            // 
            // workSplitContainer.Panel2
            // 
            this.workSplitContainer.Panel2.Controls.Add(this.srcTabControl);
            this.workSplitContainer.Size = new System.Drawing.Size(1263, 393);
            this.workSplitContainer.SplitterDistance = 246;
            this.workSplitContainer.SplitterWidth = 3;
            this.workSplitContainer.TabIndex = 0;
            // 
            // srcListViewPage
            // 
            this.srcListViewPage.Alignment = System.Windows.Forms.TabAlignment.Bottom;
            this.srcListViewPage.Controls.Add(this.srcManager);
            this.srcListViewPage.Controls.Add(this.propertyGrid);
            this.srcListViewPage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.srcListViewPage.Location = new System.Drawing.Point(0, 0);
            this.srcListViewPage.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.srcListViewPage.Name = "srcListViewPage";
            this.srcListViewPage.SelectedIndex = 0;
            this.srcListViewPage.Size = new System.Drawing.Size(246, 393);
            this.srcListViewPage.TabIndex = 0;
            // 
            // srcManager
            // 
            this.srcManager.Controls.Add(this.treeView1);
            this.srcManager.Location = new System.Drawing.Point(4, 4);
            this.srcManager.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.srcManager.Name = "srcManager";
            this.srcManager.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.srcManager.Size = new System.Drawing.Size(238, 367);
            this.srcManager.TabIndex = 1;
            this.srcManager.Text = "资源管理器";
            this.srcManager.UseVisualStyleBackColor = true;
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeView1.Location = new System.Drawing.Point(2, 2);
            this.treeView1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(234, 363);
            this.treeView1.TabIndex = 0;
            // 
            // propertyGrid
            // 
            this.propertyGrid.Controls.Add(this.propertyGrid1);
            this.propertyGrid.Location = new System.Drawing.Point(4, 4);
            this.propertyGrid.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.propertyGrid.Name = "propertyGrid";
            this.propertyGrid.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.propertyGrid.Size = new System.Drawing.Size(238, 367);
            this.propertyGrid.TabIndex = 2;
            this.propertyGrid.Text = "属性视图";
            this.propertyGrid.UseVisualStyleBackColor = true;
            // 
            // propertyGrid1
            // 
            this.propertyGrid1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.propertyGrid1.Location = new System.Drawing.Point(2, 2);
            this.propertyGrid1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.propertyGrid1.Name = "propertyGrid1";
            this.propertyGrid1.Size = new System.Drawing.Size(234, 363);
            this.propertyGrid1.TabIndex = 0;
            // 
            // srcTabControl
            // 
            this.srcTabControl.Alignment = System.Windows.Forms.TabAlignment.Bottom;
            this.srcTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.srcTabControl.Location = new System.Drawing.Point(0, 0);
            this.srcTabControl.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.srcTabControl.Name = "srcTabControl";
            this.srcTabControl.SelectedIndex = 0;
            this.srcTabControl.Size = new System.Drawing.Size(1014, 393);
            this.srcTabControl.TabIndex = 0;
            // 
            // bottomTabPages
            // 
            this.bottomTabPages.Alignment = System.Windows.Forms.TabAlignment.Bottom;
            this.bottomTabPages.Controls.Add(this.infoPage);
            this.bottomTabPages.Controls.Add(this.logPage);
            this.bottomTabPages.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bottomTabPages.Location = new System.Drawing.Point(0, 0);
            this.bottomTabPages.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.bottomTabPages.Name = "bottomTabPages";
            this.bottomTabPages.SelectedIndex = 0;
            this.bottomTabPages.Size = new System.Drawing.Size(1263, 186);
            this.bottomTabPages.TabIndex = 0;
            // 
            // logPage
            // 
            this.logPage.Controls.Add(this.richTextBox1);
            this.logPage.Location = new System.Drawing.Point(4, 4);
            this.logPage.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.logPage.Name = "logPage";
            this.logPage.Padding = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.logPage.Size = new System.Drawing.Size(1255, 160);
            this.logPage.TabIndex = 0;
            this.logPage.Text = "输出";
            this.logPage.UseVisualStyleBackColor = true;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBox1.Location = new System.Drawing.Point(2, 2);
            this.richTextBox1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(1251, 156);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = "";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(181, 6);
            // 
            // 重新关联oe文件ToolStripMenuItem
            // 
            this.重新关联oe文件ToolStripMenuItem.Name = "重新关联oe文件ToolStripMenuItem";
            this.重新关联oe文件ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.重新关联oe文件ToolStripMenuItem.Text = "重新关联.oe文件";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(181, 6);
            // 
            // infoPage
            // 
            this.infoPage.Location = new System.Drawing.Point(4, 4);
            this.infoPage.Name = "infoPage";
            this.infoPage.Padding = new System.Windows.Forms.Padding(3);
            this.infoPage.Size = new System.Drawing.Size(1255, 160);
            this.infoPage.TabIndex = 1;
            this.infoPage.Text = "提示";
            this.infoPage.UseVisualStyleBackColor = true;
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(181, 6);
            // 
            // 转换为大写ToolStripMenuItem
            // 
            this.转换为大写ToolStripMenuItem.Name = "转换为大写ToolStripMenuItem";
            this.转换为大写ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.转换为大写ToolStripMenuItem.Text = "转换为大写";
            // 
            // 转换为小写ToolStripMenuItem
            // 
            this.转换为小写ToolStripMenuItem.Name = "转换为小写ToolStripMenuItem";
            this.转换为小写ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.转换为小写ToolStripMenuItem.Text = "转换为小写";
            // 
            // 新建ToolStripButton
            // 
            this.新建ToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.新建ToolStripButton.Image = global::GUI.Properties.Resources.NewFile_16x;
            this.新建ToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.新建ToolStripButton.Name = "新建ToolStripButton";
            this.新建ToolStripButton.Size = new System.Drawing.Size(24, 24);
            this.新建ToolStripButton.Text = "toolStripButton1";
            this.新建ToolStripButton.Click += new System.EventHandler(this.新建ToolStripButton_Click);
            // 
            // 打开ToolStripButton
            // 
            this.打开ToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.打开ToolStripButton.Image = global::GUI.Properties.Resources.OpenFolder_16x;
            this.打开ToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.打开ToolStripButton.Name = "打开ToolStripButton";
            this.打开ToolStripButton.Size = new System.Drawing.Size(24, 24);
            this.打开ToolStripButton.Text = "toolStripButton2";
            // 
            // 保存ToolStripButton
            // 
            this.保存ToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.保存ToolStripButton.Image = global::GUI.Properties.Resources.Save_16x;
            this.保存ToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.保存ToolStripButton.Name = "保存ToolStripButton";
            this.保存ToolStripButton.Size = new System.Drawing.Size(24, 24);
            this.保存ToolStripButton.Text = "toolStripButton3";
            // 
            // 另存为ToolStripButton
            // 
            this.另存为ToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.另存为ToolStripButton.Image = global::GUI.Properties.Resources.SaveAs_16x;
            this.另存为ToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.另存为ToolStripButton.Name = "另存为ToolStripButton";
            this.另存为ToolStripButton.Size = new System.Drawing.Size(24, 24);
            this.另存为ToolStripButton.Text = "toolStripButton4";
            // 
            // 新建ToolStripMenuItem
            // 
            this.新建ToolStripMenuItem.Image = global::GUI.Properties.Resources.NewFile_16x;
            this.新建ToolStripMenuItem.Name = "新建ToolStripMenuItem";
            this.新建ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.新建ToolStripMenuItem.Text = "新建";
            this.新建ToolStripMenuItem.Click += new System.EventHandler(this.新建ToolStripMenuItem_Click);
            // 
            // 打开ToolStripMenuItem
            // 
            this.打开ToolStripMenuItem.Image = global::GUI.Properties.Resources.OpenFolder_16x;
            this.打开ToolStripMenuItem.Name = "打开ToolStripMenuItem";
            this.打开ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.打开ToolStripMenuItem.Text = "打开";
            // 
            // 保存ToolStripMenuItem
            // 
            this.保存ToolStripMenuItem.Image = global::GUI.Properties.Resources.Save_16x;
            this.保存ToolStripMenuItem.Name = "保存ToolStripMenuItem";
            this.保存ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.保存ToolStripMenuItem.Text = "保存";
            // 
            // 另存为ToolStripMenuItem
            // 
            this.另存为ToolStripMenuItem.Image = global::GUI.Properties.Resources.SaveAs_16x;
            this.另存为ToolStripMenuItem.Name = "另存为ToolStripMenuItem";
            this.另存为ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.另存为ToolStripMenuItem.Text = "另存为";
            // 
            // 最近工程ToolStripMenuItem
            // 
            this.最近工程ToolStripMenuItem.Image = global::GUI.Properties.Resources.History_16x;
            this.最近工程ToolStripMenuItem.Name = "最近工程ToolStripMenuItem";
            this.最近工程ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.最近工程ToolStripMenuItem.Text = "最近工程";
            // 
            // 关闭ToolStripMenuItem
            // 
            this.关闭ToolStripMenuItem.Image = global::GUI.Properties.Resources.Close_16x;
            this.关闭ToolStripMenuItem.Name = "关闭ToolStripMenuItem";
            this.关闭ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.关闭ToolStripMenuItem.Text = "关闭";
            this.关闭ToolStripMenuItem.Click += new System.EventHandler(this.关闭ToolStripMenuItem_Click);
            // 
            // 剪切ToolStripMenuItem
            // 
            this.剪切ToolStripMenuItem.Image = global::GUI.Properties.Resources.Cut_16x;
            this.剪切ToolStripMenuItem.Name = "剪切ToolStripMenuItem";
            this.剪切ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.剪切ToolStripMenuItem.Text = "剪切";
            // 
            // 复制ToolStripMenuItem
            // 
            this.复制ToolStripMenuItem.Image = global::GUI.Properties.Resources.Copy_16x;
            this.复制ToolStripMenuItem.Name = "复制ToolStripMenuItem";
            this.复制ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.复制ToolStripMenuItem.Text = "复制";
            // 
            // 粘贴ToolStripMenuItem
            // 
            this.粘贴ToolStripMenuItem.Image = global::GUI.Properties.Resources.Paste_16x;
            this.粘贴ToolStripMenuItem.Name = "粘贴ToolStripMenuItem";
            this.粘贴ToolStripMenuItem.Size = new System.Drawing.Size(184, 26);
            this.粘贴ToolStripMenuItem.Text = "粘贴";
            // 
            // 剪切ToolStripButton
            // 
            this.剪切ToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.剪切ToolStripButton.Image = global::GUI.Properties.Resources.Cut_16x;
            this.剪切ToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.剪切ToolStripButton.Name = "剪切ToolStripButton";
            this.剪切ToolStripButton.Size = new System.Drawing.Size(24, 24);
            this.剪切ToolStripButton.Text = "toolStripButton5";
            // 
            // 复制ToolStripButton
            // 
            this.复制ToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.复制ToolStripButton.Image = global::GUI.Properties.Resources.Copy_16x;
            this.复制ToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.复制ToolStripButton.Name = "复制ToolStripButton";
            this.复制ToolStripButton.Size = new System.Drawing.Size(24, 24);
            this.复制ToolStripButton.Text = "toolStripButton6";
            // 
            // 粘贴ToolStripButton
            // 
            this.粘贴ToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.粘贴ToolStripButton.Image = global::GUI.Properties.Resources.Paste_16x;
            this.粘贴ToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.粘贴ToolStripButton.Name = "粘贴ToolStripButton";
            this.粘贴ToolStripButton.Size = new System.Drawing.Size(24, 24);
            this.粘贴ToolStripButton.Text = "toolStripButton7";
            // 
            // toolStripButton8
            // 
            this.toolStripButton8.Name = "toolStripButton8";
            this.toolStripButton8.Size = new System.Drawing.Size(6, 27);
            // 
            // MainWnd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1263, 656);
            this.Controls.Add(this.mainSplitContainer);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.mainStatusStrip);
            this.Controls.Add(this.mainMenuStrip);
            this.MainMenuStrip = this.mainMenuStrip;
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "MainWnd";
            this.Text = "开源易语言集成开发环境";
            this.mainMenuStrip.ResumeLayout(false);
            this.mainMenuStrip.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.mainSplitContainer.Panel1.ResumeLayout(false);
            this.mainSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.mainSplitContainer)).EndInit();
            this.mainSplitContainer.ResumeLayout(false);
            this.workSplitContainer.Panel1.ResumeLayout(false);
            this.workSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.workSplitContainer)).EndInit();
            this.workSplitContainer.ResumeLayout(false);
            this.srcListViewPage.ResumeLayout(false);
            this.srcManager.ResumeLayout(false);
            this.propertyGrid.ResumeLayout(false);
            this.bottomTabPages.ResumeLayout(false);
            this.logPage.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip mainMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem 文件FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 编辑ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 导航ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 视图ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 调试ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 编译ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 帮助ToolStripMenuItem;
        private System.Windows.Forms.StatusStrip mainStatusStrip;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.SplitContainer mainSplitContainer;
        private System.Windows.Forms.SplitContainer workSplitContainer;
        private System.Windows.Forms.TabControl bottomTabPages;
        private System.Windows.Forms.TabPage logPage;
        private System.Windows.Forms.TabControl srcListViewPage;
        private System.Windows.Forms.TabPage srcManager;
        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.TabPage propertyGrid;
        private System.Windows.Forms.PropertyGrid propertyGrid1;
        private System.Windows.Forms.TabControl srcTabControl;
        private System.Windows.Forms.ToolStripMenuItem 新建ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 打开ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 另存为ToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 重新关联oe文件ToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem 最近工程ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关闭ToolStripMenuItem;
        private System.Windows.Forms.ToolStripButton 新建ToolStripButton;
        private System.Windows.Forms.ToolStripButton 打开ToolStripButton;
        private System.Windows.Forms.TabPage infoPage;
        private System.Windows.Forms.ToolStripButton 保存ToolStripButton;
        private System.Windows.Forms.ToolStripButton 另存为ToolStripButton;
        private System.Windows.Forms.ToolStripMenuItem 剪切ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 复制ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 粘贴ToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem 转换为大写ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 转换为小写ToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton 剪切ToolStripButton;
        private System.Windows.Forms.ToolStripButton 复制ToolStripButton;
        private System.Windows.Forms.ToolStripButton 粘贴ToolStripButton;
        private System.Windows.Forms.ToolStripSeparator toolStripButton8;
    }
}

