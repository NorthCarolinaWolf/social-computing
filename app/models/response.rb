class Response < ActiveRecord::Base
  belongs_to :request
  
  def self.fill (id)
      
      @request=Request.find(id)
      val=%x( python lib/test.py '#{@request.content}')
      puts '+++++++++++'
      puts val
    #   @response=@request.responses.build(name:"autofill-contact",contact:"autofill-contact",content:"autofill-content")
    #   return @response.save
      return true
     
  end
  
end
