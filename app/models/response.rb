class Response < ActiveRecord::Base
  belongs_to :request
  
  def self.fill (id)
      
      @request=Request.find(id)
      @content=@request.content
      @content.sub! '\'', '\\\''
      @argument=  "\"#{@content}\""
      
      #val=%x( python lib/TextClassifier.py "\"#{@request.content}\"")
      val=%x( python lib/TextClassifier.py "#{@argument}")
      if val.include? "None"
        @response=@request.responses.build(name:'sorry',contact:'sorry',content:'we can\'t find any related field')
      else
        strs=val.split('$')
        @response=@request.responses.build(name:strs[0],contact:strs[1],content:strs[2])
      end
      return @response
     
  end
  
end
