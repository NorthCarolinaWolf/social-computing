class Response < ActiveRecord::Base
  belongs_to :request
  
  def self.fill (id)
      
      @request=Request.find(id)
      val=%x( python lib/TextClassifier.py "\"#{@request.content}\"")
      strs=val.split('$')
      if strs[0]=='T'
        @response=@request.responses.build(name:'sorry',contact:'sorry',content:'we can\'t find any related field')
      else
        @response=@request.responses.build(name:strs[0],contact:strs[1],content:strs[2])
      end
      return @response
     
  end
  
end
