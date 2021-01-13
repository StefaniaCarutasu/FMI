namespace CarutasuAdrianaS43.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class Initial2 : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Domains",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        Denumire = c.String(nullable: false),
                    })
                .PrimaryKey(t => t.Id);
            
            CreateTable(
                "dbo.Students",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        Nume = c.String(nullable: false),
                        Email = c.String(nullable: false, maxLength: 25),
                        DataNastere = c.DateTime(nullable: false),
                        DomainId = c.Int(nullable: false),
                    })
                .PrimaryKey(t => t.Id)
                .ForeignKey("dbo.Domains", t => t.DomainId, cascadeDelete: true)
                .Index(t => t.DomainId);
            
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.Students", "DomainId", "dbo.Domains");
            DropIndex("dbo.Students", new[] { "DomainId" });
            DropTable("dbo.Students");
            DropTable("dbo.Domains");
        }
    }
}
