class CreateResponses < ActiveRecord::Migration
  def change
    create_table :responses do |t|
      t.string :name
      t.string :contact
      t.text :content
      t.references :request, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
