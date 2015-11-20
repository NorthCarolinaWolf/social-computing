class RequestsController < ApplicationController
    def new
        @request = Request.new
    end
    
    def create
         @request=Request.new(params.require(:request).permit(:name,:contact,:content))
    if @request.save
       redirect_to action: "show", id:@request.id
    else
      render 'new'
    end
   
    end
    
    def show
        @request=Request.find(params[:id])
    end
    
end
